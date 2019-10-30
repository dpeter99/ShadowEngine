#include "shpch.h"

#include "Core/Core.h"

#include "D3D12RendererAPI.h"
#include "D3D12Context.h"
#include "D3D12CommandQueue.h"
#include "ShadowAsset/Assets/Mesh.h"
#include "D3D12Shader.h"

namespace ShadowEngine::Rendering::D3D12 {

	com_ptr<ID3D12Device> D3D12RendererAPI::device{ nullptr };
	Ref<D3D12::D3D12Context> D3D12RendererAPI::ctx {nullptr};
	
	
	
	/**
	 * \brief Loads the GPU adapters
	 * \param dxgiFactory DXGI factory instance
	 * \param adapters Returns the Vector of adapters
	 */
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
	
	void D3D12RendererAPI::Init(ShadowEngine::Ref<GraphicsContext> _ctx)
	{
		this->ctx = std::dynamic_pointer_cast<D3D12Context>(_ctx);
		
		//Load in the GPU adapters
		std::vector<com_ptr<IDXGIAdapter1>> adapters;
		GetAdapters(ctx->dxgiFactory.Get(), adapters);	

		// select your adapter here, NULL = system default
		// Using the first adapter for now
		IUnknown* selectedAdapter = (adapters.size() > 0) ? adapters[0].Get() : NULL;

		com_ptr<ID3D12Debug> debug_controller;
		D3D12GetDebugInterface(IID_PPV_ARGS(&debug_controller));
		debug_controller->EnableDebugLayer();
		
		//Create the D3D device
		DX_API("Failed to create D3D Device")
			D3D12CreateDevice(selectedAdapter, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(device.GetAddressOf()));

		
		
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
		
		command_queue = std::make_shared<D3D12::D3D12CommandQueue>();
		command_list = std::make_shared<D3D12::D3D12CommandList>();
		
		swap_chain = std::make_shared<D3D12::D3D12SwapChain>(command_queue,ctx->window->Width, ctx->window->Height);
		depth_buffer = std::make_shared<D3D12::D3D12DepthBuffer>(scissorRect);
		
		fence = std::make_unique<D3D12::D3D12Fence>();
		fenceValue = 0;

		fenceEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		if (fenceEvent == NULL) {
			DX_API("Failed to create windows event") HRESULT_FROM_WIN32(GetLastError());
		}		
	}

	void D3D12RendererAPI::SetClearColor(const glm::vec4& color)
	{

	}

	void D3D12RendererAPI::Clear()
	{
		
	}

	void D3D12RendererAPI::Draw(const Ref<Assets::Mesh> mesh, const Ref<Assets::Material> material, const glm::mat4& transform)
	{		
		Ref<D3D12Shader> dx12_shader = std::dynamic_pointer_cast<D3D12::D3D12Shader>(material->GetShader());
		command_list->UseShader(dx12_shader);
		command_list->BindConstantBuffer(material->GetBuffer(), dx12_shader->GetMaterialSlotIndex());
		command_list->DrawMesh(mesh);
	}

	void D3D12RendererAPI::Draw(const std::shared_ptr<Assets::Mesh>& mesh, const std::shared_ptr<Assets::Material>& material, const ConstantBuffer& meshData)
	{
		Ref<D3D12Shader> dx12_shader = std::dynamic_pointer_cast<D3D12::D3D12Shader>(material->GetShader());
		command_list->UseShader(dx12_shader);
		command_list->BindConstantBuffer(worldData, 0);
		command_list->BindConstantBuffer(meshData, 1);
		command_list->BindConstantBuffer(material->GetBuffer(), dx12_shader->GetMaterialSlotIndex());
		command_list->DrawMesh(mesh);
	}

	void D3D12RendererAPI::StartFrame(Ref<ConstantBuffer> worldCB)
	{
		command_list->Reset();

		command_list->SetViewports(viewPort);
		command_list->SetScissorRects(scissorRect);

		auto entry_barrier = CD3DX12_RESOURCE_BARRIER::Transition(
			swap_chain->GetCurrentRenderTarget().Get(),
			D3D12_RESOURCE_STATE_PRESENT,
			D3D12_RESOURCE_STATE_RENDER_TARGET);
		
		command_list->ResourceBarrier(&entry_barrier);

		command_list->SetRenderTargets(swap_chain, depth_buffer);

		const float clearColor[] = { 0.0f, 0.2f, 0.4f, 1.0f };
		command_list->ClearRenderTargetView(clearColor);
		command_list->ClearDepthStencilView(1.0f,0);

		worldData=worldCB;
	}

	void D3D12RendererAPI::EndFrame()
	{
		auto end_barrier = CD3DX12_RESOURCE_BARRIER::Transition(
			swap_chain->GetCurrentRenderTarget().Get(),
			D3D12_RESOURCE_STATE_RENDER_TARGET,
			D3D12_RESOURCE_STATE_PRESENT);

		command_list->ResourceBarrier(&end_barrier);

		command_list->Close();

		//TODO:move this to submitting code
		command_queue->Execute(command_list);

		swap_chain->Present(1, 0);

		WaitForPreviousFrame();
	}

	void D3D12RendererAPI::WaitForPreviousFrame() {
		const UINT64 fv = fenceValue;
		
		command_queue->Signal(fence, fv);

		fenceValue++;

		if (fence->GetCompletedValue() < fv) {
			
				fence->SetEventOnCompletion(fv, fenceEvent);
			WaitForSingleObject(fenceEvent, INFINITE);
		}

		swap_chain->UpdateCurrentBackBufferIndex();
	}

}
