#include "shpch.h"

#include "Core/Core.h"

#include "DX12RendererAPI.h"
#include "D3D12Context.h"
#include "D3D12CommandQueue.h"
#include "Assets/Assets/Mesh.h"
#include "D3D12Shader.h"
#include "D3D12MaterialImpl.h"
#include "Core/ShadowApplication.h"
#include "ImGui/ImGuiModule.h"
#include "D3D12SwapChain.h"

namespace ShadowEngine::Rendering::D3D12 {

	com_ptr<ID3D12Device> DX12RendererAPI::device{ nullptr };
	Ref<D3D12::D3D12Context> DX12RendererAPI::ctx {nullptr};
	
	DX12RendererAPI* DX12RendererAPI::Instance{ nullptr };
	
	/// <summary>
	/// Loads the GPU adapters
	/// </summary>
	/// <param name="dxgiFactory">DXGI factory instance</param>
	/// <param name="adapters">Returns the Vector of adapters</param>
	void GetAdapters(IDXGIFactory6* dxgiFactory, std::vector<com_ptr<IDXGIAdapter1>>& adapters) {
		HRESULT adapterQueryResult;
		unsigned int adapterId = 0;
		OutputDebugStringW(L"Detected Video Adapters:\n");
		do {
			com_ptr<IDXGIAdapter1> tempAdapter{ nullptr };
			adapterQueryResult = dxgiFactory->EnumAdapters1(adapterId, tempAdapter.GetAddressOf());

			if (adapterQueryResult != S_OK && adapterQueryResult != DXGI_ERROR_NOT_FOUND) {
				ASSERT(false, "Failed to query DXGI adapter");
			}

			if (tempAdapter != nullptr) {
				DXGI_ADAPTER_DESC desc;
				tempAdapter->GetDesc(&desc);

				OutputDebugStringW(L"\t");
				OutputDebugStringW(desc.Description);
				OutputDebugStringW(L"\n");

				adapters.push_back(std::move(tempAdapter));
			}

			adapterId++;
		} while (adapterQueryResult != DXGI_ERROR_NOT_FOUND);
	}

	IDXGIAdapter1* FindDevice(IDXGIFactory6* dxgiFactory) {
		// adapters are the graphics cards (this includes the embedded graphics on the motherboard)
		IDXGIAdapter1* adapter; 

		// we'll start looking for directx 12  compatible graphics devices starting at index 0
		int adapterIndex = 0; 

		// set this to true when a good one was found
		bool adapterFound = false; 

		// find first hardware gpu that supports d3d 12
		while (dxgiFactory->EnumAdapters1(adapterIndex, &adapter) != DXGI_ERROR_NOT_FOUND)
		{
			DXGI_ADAPTER_DESC1 desc;
			adapter->GetDesc1(&desc);

			if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
			{
				// we dont want a software device
				adapterIndex++;
				continue;
			}

			// we want a device that is compatible with direct3d 12 (feature level 11 or higher)
			HRESULT hr;
			//TODO: Also check for largest memory
			hr = D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_12_1, _uuidof(ID3D12Device), nullptr);
			if (SUCCEEDED(hr))
			{
				adapterFound = true;
				break;
			}

			adapterIndex++;
		}

		if (!adapterFound)
		{
			return nullptr;
		}

		return adapter;
	}
	
	void DX12RendererAPI::Init(ShadowEngine::Ref<GraphicsContext> _ctx)
	{
		assert(Instance == nullptr);
		Instance = this;
		
		this->ctx = std::dynamic_pointer_cast<D3D12Context>(_ctx);

		com_ptr<ID3D12Debug> debug_controller;
		D3D12GetDebugInterface(IID_PPV_ARGS(&debug_controller));
		debug_controller->EnableDebugLayer();
		
		IDXGIAdapter1* adapter = FindDevice(ctx->dxgiFactory.Get());
		//Create the D3D device
		DX_API("Failed to create D3D Device")
			D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(device.GetAddressOf()));

		
		if (device == nullptr) {
			throw new std::exception("No graphics card");
		}
		
		viewPort.TopLeftX = 0;
		viewPort.TopLeftY = 0;
		viewPort.Width = ctx->window->Width;
		viewPort.Height = ctx->window->Height;
		viewPort.MinDepth = 0.0f;
		viewPort.MaxDepth = 1.0f;

		aspectRatio = viewPort.Width / (float)viewPort.Height;

		scissorRect.left = 0;
		scissorRect.top = 0;
		scissorRect.right = ctx->window->Width;
		scissorRect.bottom = ctx->window->Height;
		
		//Create dx12 render resources

		// Create descriptor allocators
		for (int i = 0; i < D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES; ++i)
		{
			m_DescriptorAllocators[i] = std::make_unique<DescriptorAllocator>(static_cast<D3D12_DESCRIPTOR_HEAP_TYPE>(i));
		}
		
		command_queue = std::make_shared<D3D12::D3D12CommandQueue>();
		command_queue->SetName(L"Main graphics queue");

		command_allocator_pool = std::make_shared<D3D12::CommandAllocatorPool>();
		
		command_list = std::make_shared<D3D12::CommandList>();
		command_list->SetName(L"Main graphics list");
		
		swap_chain = std::make_shared<D3D12::D3D12SwapChain>(command_queue,ctx->window->Width, ctx->window->Height);
		depth_buffer = std::make_shared<D3D12::D3D12DepthBuffer>(scissorRect);
		

		upload_managger = std::make_shared<UploadManagger>();

	}

	void DX12RendererAPI::SetClearColor(const glm::vec4& color)
	{
		clearColor = color;
	}

	void DX12RendererAPI::Clear()
	{
		SH_CORE_CRITICAL("This call is not used and should not be called How did we get here? {0}", __FILE__);
	}

	void DX12RendererAPI::Draw(const std::shared_ptr<Assets::Mesh>& mesh, const std::shared_ptr<Assets::Material>& material, const ConstantBuffer& meshData)
	{
		Ref<DX12Shader> dx12_shader = std::dynamic_pointer_cast<D3D12::DX12Shader>(material->GetShader());
		command_list->XDEP_UseShader(dx12_shader);
		
		command_list->XDEP_BindConstantBuffer(worldData, 0);
		command_list->XDEP_BindConstantBuffer(meshData, 1);

		D3D12MaterialImpl* dx12_mat = (D3D12MaterialImpl*)material->getImpl().get();
		dx12_mat->BindMaterialData(command_list);
		
		command_list->XDEP_DrawMesh(mesh);
	}

	
	void DX12RendererAPI::StartFrame(Ref<ConstantBuffer> worldCB, uint64_t frame)
	{
		frame_index = command_queue->GetNextSignalValue();
		
		//Reset the command list
		command_list->Reset(frame_index, command_queue);

		//Set render area
		command_list->SetViewports(viewPort);
		command_list->SetScissorRects(scissorRect);

		//Wait for the render target to transition
		auto entry_barrier = CD3DX12_RESOURCE_BARRIER::Transition(
			swap_chain->GetCurrentRenderTarget().Get(),
			D3D12_RESOURCE_STATE_PRESENT,
			D3D12_RESOURCE_STATE_RENDER_TARGET);
		
		command_list->ResourceBarrier(&entry_barrier);

		//Set the render targets
		command_list->SetRenderTargets(swap_chain, depth_buffer);

		//Clear the render target
		command_list->ClearRenderTargetView((float*)&clearColor);
		command_list->ClearDepthStencilView(1.0f,0);

		//Assign the descriptor heaps
		//std::vector<com_ptr<ID3D12DescriptorHeap>> heaps;

		
		worldData=worldCB;

		upload_managger->CheckForFnishedUploads();


		if(ShadowApplication::Get().GetModuleManager().GetModuleByType< DebugGui::ImGuiModule>() != nullptr)
		DebugGui::ImGuiModule::StartFrame();
	}

	void DX12RendererAPI::EndFrame()
	{
		auto end_barrier = CD3DX12_RESOURCE_BARRIER::Transition(
			swap_chain->GetCurrentRenderTarget().Get(),
			D3D12_RESOURCE_STATE_RENDER_TARGET,
			D3D12_RESOURCE_STATE_PRESENT);

		command_list->ResourceBarrier(&end_barrier);

		command_list->Close();

		//TODO:move this to submitting code
		command_queue->Execute(command_list);

		if (ShadowApplication::Get().GetModuleManager().GetModuleByType< DebugGui::ImGuiModule>() != nullptr)
		DebugGui::ImGuiModule::OtherWindows();
		
		swap_chain->Present(1, 0);

		//Signal the end of the frame
		frame_index = command_queue->Signal();
		//Save out the frame id to the swap chain
		swap_chain->SetCurrentRenderTargetFenceValue(frame_index);		
		
		StartResourceUpload();

		swap_chain->FindNextBackBufferIndex();

		//fence->WaitForValue(swap_chain->GetCurrentRenderTargetFenceValue());
		command_queue->WaitForFenceValue(swap_chain->GetCurrentRenderTargetFenceValue());

		command_allocator_pool->CheckFinished(swap_chain->GetCurrentRenderTargetFenceValue(), command_queue);

	}

	
	void DX12RendererAPI::UploadResource(Ref<D3D12IUploadable> resource)
	{
		upload_managger->Upload(resource);
	}

	void DX12RendererAPI::UploadResource(D3D12IUploadable* resource)
	{
		upload_managger->Upload(Ref<D3D12IUploadable>(resource));
	}
	
	void DX12RendererAPI::StartResourceUpload()
	{
		upload_managger->SubmitUploads();
	}

	
	UINT DX12RendererAPI::GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE type) const
	{
		return device->GetDescriptorHandleIncrementSize(type);
	}

	
	DescriptorAllocation DX12RendererAPI::AllocateDescriptors(D3D12_DESCRIPTOR_HEAP_TYPE type, uint32_t numDescriptors)
	{
		return m_DescriptorAllocators[type]->Allocate(numDescriptors);
	}

	void DX12RendererAPI::ReleaseStaleDescriptors(uint64_t finishedFrame)
	{
		for (int i = 0; i < D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES; ++i)
		{
			m_DescriptorAllocators[i]->ReleaseStaleDescriptors(finishedFrame);
		}
	}

	
	com_ptr<ID3D12DescriptorHeap> DX12RendererAPI::CreateDescriptorHeap(UINT numDescriptors, D3D12_DESCRIPTOR_HEAP_TYPE type)
	{
		D3D12_DESCRIPTOR_HEAP_DESC desc = {};
		desc.Type = type;
		desc.NumDescriptors = numDescriptors;
		desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
		desc.NodeMask = 0;

		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap;
		DX_API("Unable to create descriptor heap")
			(device->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&descriptorHeap)));

		return descriptorHeap;
	}
}
