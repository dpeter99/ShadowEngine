#include "shpch.h"
#include "CommandList.h"
#include "DX12RendererAPI.h"
#include "D3D12Shader.h"
#include "D3D12Buffers.h"
#include "D3D12ConstantBuffer.h"
#include "Textures/Texture.h"

namespace ShadowEngine::Rendering::D3D12 {

	CommandList::CommandList(D3D12_COMMAND_LIST_TYPE type)
	{
		DX_API("Failed to create command allocator")
			DX12RendererAPI::device->CreateCommandAllocator(type, IID_PPV_ARGS(commandAllocator.GetAddressOf()));

		DX_API("Failed to greate graphics command list")
			DX12RendererAPI::device->CreateCommandList(0, type, commandAllocator.Get(), nullptr, IID_PPV_ARGS(m_commandList.GetAddressOf()));

		m_commandList->Close();

		isBeingRecorded = false;
	}



	void CommandList::Reset()
	{
		//if (isBeingRecorded)
			isBeingRecorded = true;
		
		commandAllocator->Reset();
		m_commandList->Reset(commandAllocator.Get(), nullptr);
	}

	void CommandList::StartRecording (){
		SH_CORE_ASSERT(isBeingRecorded, "Command list is already recording");
		if(!isBeingRecorded)
		isBeingRecorded = true;
	}

	
	void CommandList::SetViewports(D3D12_VIEWPORT viewPort)
	{
		m_commandList->RSSetViewports(1, &viewPort);
	}

	void CommandList::SetScissorRects(D3D12_RECT scissorRect)
	{
		m_commandList->RSSetScissorRects(1, &scissorRect);
	}

	
	void CommandList::ResourceBarrier(D3D12_RESOURCE_BARRIER* barrier)
	{
		m_commandList->ResourceBarrier(1, barrier);
	}

	void CommandList::TransitionBarrier(com_ptr<ID3D12Resource> resource, D3D12_RESOURCE_STATES stateAfter, UINT subresource, bool flushBarriers)
	{
		if (resource)
		{
			// The "before" state is not important. It will be resolved by the resource state tracker.
			auto barrier = CD3DX12_RESOURCE_BARRIER::Transition(resource.Get(), D3D12_RESOURCE_STATE_COMMON, stateAfter, subresource);
			m_ResourceStateTracker->ResourceBarrier(barrier);
		}

		if (flushBarriers)
		{
			FlushResourceBarriers();
		}
	}

	void CommandList::TransitionBarrier(const Resource& resource, D3D12_RESOURCE_STATES stateAfter, UINT subresource, bool flushBarriers)
	{
		TransitionBarrier(resource.GetD3D12Resource(), stateAfter, subresource, flushBarriers);
	}

	
	void CommandList::SetRenderTargets(Ref<D3D12SwapChain> swapchain, Ref<D3D12DepthBuffer> depthBuffer)
	{
		renderTarget = swapchain->GetCurrentRenderTargetDescriptor();
		this->depthBuffer = depthBuffer->GetDescriptorHandle();
		m_commandList->OMSetRenderTargets(1, &renderTarget, FALSE, &this->depthBuffer);
	}

	void CommandList::ClearRenderTargetView(const float* color)
	{
		m_commandList->ClearRenderTargetView(renderTarget, color, 0, nullptr);
	}

	void CommandList::ClearDepthStencilView(float depth, uint8_t stencil)
	{
		m_commandList->ClearDepthStencilView(depthBuffer, D3D12_CLEAR_FLAG_DEPTH, depth, stencil, 0, nullptr);
	}


	void CommandList::UploadToBuffer(Buffer& buffer, size_t numElements, size_t elementSize, const void* bufferData, D3D12_RESOURCE_FLAGS flags)
	{
		auto device = DX12RendererAPI::device;

		size_t bufferSize = numElements * elementSize;


		if (bufferData != nullptr)
		{
			// Create an upload resource to use as an intermediate buffer to copy the buffer resource 
			com_ptr<ID3D12Resource> uploadResource;
			DX_API("Failled to create commited resource")
			(device->CreateCommittedResource(
				&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
				D3D12_HEAP_FLAG_NONE,
				&CD3DX12_RESOURCE_DESC::Buffer(bufferSize),
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(&uploadResource)));

			D3D12_SUBRESOURCE_DATA subresourceData = {};
			subresourceData.pData = bufferData;
			subresourceData.RowPitch = bufferSize;
			subresourceData.SlicePitch = subresourceData.RowPitch;

			m_ResourceStateTracker->TransitionResource(buffer, D3D12_RESOURCE_STATE_COPY_DEST);
			FlushResourceBarriers();

			UpdateSubresources(m_commandList.Get(),  buffer.GetD3D12Resource().Get(),
				uploadResource.Get(), 0, 0, 1, &subresourceData);

			// Add references to resources so they stay in scope until the command list is reset.
			TrackResource(uploadResource);
		}
		TrackResource(buffer.GetD3D12Resource());
		
		buffer.CreateViews(numElements, elementSize);
	}

	

	void CommandList::CopyTextureSubresource(Texture& destination, uint32_t firstSubresource, uint32_t numSubresources, D3D12_SUBRESOURCE_DATA* subresourceData)
	{
		auto device = DX12RendererAPI::device;
		auto destinationResource = destination.GetD3D12Resource();

		if (destinationResource)
		{
			// Resource must be in the copy-destination state.
			TransitionBarrier(destination, D3D12_RESOURCE_STATE_COPY_DEST);
			FlushResourceBarriers();

			UINT64 requiredSize = GetRequiredIntermediateSize(destinationResource.Get(), firstSubresource, numSubresources);

			// Create a temporary (intermediate) resource for uploading the subresources
			com_ptr<ID3D12Resource> intermediateResource;
			DX_API("Failled to create upload resource for texture")
			(device->CreateCommittedResource(
				&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
				D3D12_HEAP_FLAG_NONE,
				&CD3DX12_RESOURCE_DESC::Buffer(requiredSize),
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(&intermediateResource)
			));

			UpdateSubresources(m_commandList.Get(), destinationResource.Get(), intermediateResource.Get(), 0, firstSubresource, numSubresources, subresourceData);

			TrackResource(intermediateResource);
			TrackResource(destinationResource);
		}
	}

	
	void CommandList::Close()
	{
		assert(isBeingRecorded);

		isBeingRecorded = false;

		DX_API("Failed to close command list")
			m_commandList->Close();
	}

	bool CommandList::IsRecording()
	{
		return this->isBeingRecorded;
	}

	void CommandList::UseShader(const Ref<DX12Shader>& shader)
	{
		m_commandList->SetPipelineState(shader->GetPipelineState().Get());
		m_commandList->SetGraphicsRootSignature(shader->GetRootSignature().Get());
	}
	
	void CommandList::DrawMesh(const std::shared_ptr<Assets::Mesh>& mesh)
	{
		auto index = std::dynamic_pointer_cast<D3D12IndexBuffer>(mesh->index_buffer);
		auto vert = std::dynamic_pointer_cast<D3D12VertexBuffer>(mesh->vertex_buffer);
		
		m_commandList->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_commandList->IASetIndexBuffer(&index->GetBufferView());
		m_commandList->IASetVertexBuffers(0, 1, &vert->GetBufferView());
		m_commandList->DrawIndexedInstanced(index->GetCount(), 1, 0, 0, 0);
	}

	void CommandList::BindConstantBuffer(const Ref<ConstantBuffer>& buffer, int registerIndex)
	{
		DX12ConstantBuffer* dx12_buffer = (DX12ConstantBuffer*)buffer->GetImpl().get();
		//Ref<DX12ConstantBuffer> dx12_buffer = std::dynamic_pointer_cast<D3D12::DX12ConstantBuffer>(buffer->GetImpl());
		m_commandList->SetGraphicsRootConstantBufferView(registerIndex, dx12_buffer->GetGPUVirtualAddress());
	}

	void CommandList::BindConstantBuffer(const ConstantBuffer& buffer, int registerIndex)
	{
		DX12ConstantBuffer* dx12_buffer = (DX12ConstantBuffer*)buffer.GetImpl().get();
		//Ref<DX12ConstantBuffer> dx12_buffer = std::dynamic_pointer_cast<D3D12::DX12ConstantBuffer>(buffer.GetImpl());
		m_commandList->SetGraphicsRootConstantBufferView(registerIndex, dx12_buffer->GetGPUVirtualAddress());
	}
	
	void CommandList::BindDescriptorTableBuffer(const CD3DX12_GPU_DESCRIPTOR_HANDLE& handle, int registerIndex)
	{
		D3D12_GPU_DESCRIPTOR_HANDLE h = handle;
		m_commandList->SetGraphicsRootDescriptorTable(registerIndex, h);
	}

	void CommandList::SetDescriptorHeaps(int count, ID3D12DescriptorHeap* const* descriptorHeaps)
	{
		m_commandList->SetDescriptorHeaps(count,descriptorHeaps);
	}

	void CommandList::SetGraphicsDynamicConstantBuffer(uint32_t rootParameterIndex, size_t sizeInBytes, const void* bufferData)
	{
		// Constant buffers must be 256-byte aligned.
		auto heapAllococation = m_UploadBuffer->Allocate(sizeInBytes, D3D12_CONSTANT_BUFFER_DATA_PLACEMENT_ALIGNMENT);
		memcpy(heapAllococation.CPU, bufferData, sizeInBytes);

		m_commandList->SetGraphicsRootConstantBufferView(rootParameterIndex, heapAllococation.GPU);
	}
	
	/*
	void CommandList::SetDescriptorHeaps(std::vector<Ref<D3D12DescriptorHeap>> descriptorHeaps)
	{
		std::vector< ID3D12DescriptorHeap*> heaps;
		for (auto && descriptorHeap : descriptorHeaps)
		{
			heaps.push_back(descriptorHeap->Get().Get());
		}
		ID3D12DescriptorHeap** data = heaps.data();
		commandList->SetDescriptorHeaps(descriptorHeaps.size(), data);
	}
	*/
	
	void CommandList::SetDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType, ID3D12DescriptorHeap* heap)
	{
		if (m_DescriptorHeaps[heapType] != heap)
		{
			m_DescriptorHeaps[heapType] = heap;
			BindDescriptorHeaps();
		}
	}

	void CommandList::BindDescriptorHeaps()
	{
		UINT numDescriptorHeaps = 0;
		ID3D12DescriptorHeap* descriptorHeaps[D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES] = {};

		for (uint32_t i = 0; i < D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES; ++i)
		{
			ID3D12DescriptorHeap* descriptorHeap = m_DescriptorHeaps[i];
			if (descriptorHeap)
			{
				descriptorHeaps[numDescriptorHeaps++] = descriptorHeap;
			}
		}

		m_commandList->SetDescriptorHeaps(numDescriptorHeaps, descriptorHeaps);
	}

	void CommandList::SetShaderResourceView(uint32_t rootParameterIndex,
		uint32_t descriptorOffset,
		const Resource& resource,
		D3D12_RESOURCE_STATES stateAfter,
		UINT firstSubresource,
		UINT numSubresources,
		const D3D12_SHADER_RESOURCE_VIEW_DESC* srv)
	{
		if (numSubresources < D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES)
		{
			for (uint32_t i = 0; i < numSubresources; ++i)
			{
				TransitionBarrier(resource, stateAfter, firstSubresource + i);
			}
		}
		else
		{
			TransitionBarrier(resource, stateAfter);
		}

		m_DynamicDescriptorHeap[D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV]->StageDescriptors(rootParameterIndex, descriptorOffset, 1, resource.GetShaderResourceView(srv));

		TrackResource(resource);
	}

	void CommandList::SetShaderConstandBufferView(uint32_t rootParameterIndex, uint32_t descriptorOffset, const Buffer& resource, UINT firstSubresource, UINT numSubresources, const D3D12_CONSTANT_BUFFER_VIEW_DESC* cbv)
	{
		m_DynamicDescriptorHeap[D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV]->StageDescriptors(rootParameterIndex, descriptorOffset, 1, resource.GetConstantBufferView(cbv));

		TrackResource(resource);
	}
	

	void CommandList::FlushResourceBarriers()
	{
		m_ResourceStateTracker->FlushResourceBarriers(*this);
	}

	void CommandList::TrackResource(Microsoft::WRL::ComPtr<ID3D12Object> object)
	{
		m_TrackedObjects.push_back(object);
	}

	void CommandList::TrackResource(const Resource& res)
	{
		TrackResource(res.GetD3D12Resource());
	}
	
	void CommandList::CopyTextureRegion(CD3DX12_TEXTURE_COPY_LOCATION* from, CD3DX12_TEXTURE_COPY_LOCATION* to)
	{
		m_commandList->CopyTextureRegion(to, 0, 0, 0, from, nullptr);
	}
}
