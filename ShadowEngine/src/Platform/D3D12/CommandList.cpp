#include "shpch.h"
#include "CommandList.h"
#include "DX12RendererAPI.h"
#include "D3D12Shader.h"
#include "D3D12Buffers.h"
#include "D3D12ConstantBuffer.h"

namespace ShadowEngine::Rendering::D3D12 {

	CommandList::CommandList(D3D12_COMMAND_LIST_TYPE type)
	{
		DX_API("Failed to create command allocator")
			DX12RendererAPI::device->CreateCommandAllocator(type, IID_PPV_ARGS(commandAllocator.GetAddressOf()));

		DX_API("Failed to greate graphics command list")
			DX12RendererAPI::device->CreateCommandList(0, type, commandAllocator.Get(), nullptr, IID_PPV_ARGS(commandList.GetAddressOf()));

		commandList->Close();

		isBeingRecorded = false;
	}

	void CommandList::UseShader(const Ref<DX12Shader>& shader)
	{
		commandList->SetPipelineState(shader->GetPipelineState().Get());
		commandList->SetGraphicsRootSignature(shader->GetRootSignature().Get());
	}

	void CommandList::Reset()
	{
		//if (isBeingRecorded)
			isBeingRecorded = true;
		
		commandAllocator->Reset();
		commandList->Reset(commandAllocator.Get(), nullptr);
	}

	void CommandList::StartRecording [[deprecated]] ()
	{
		SH_CORE_ASSERT(isBeingRecorded, "Command list is already recording");
		
		if(!isBeingRecorded)
		isBeingRecorded = true;
			
	}

	void CommandList::SetViewports(D3D12_VIEWPORT viewPort)
	{
		commandList->RSSetViewports(1, &viewPort);
	}

	void CommandList::SetScissorRects(D3D12_RECT scissorRect)
	{
		commandList->RSSetScissorRects(1, &scissorRect);
	}

	void CommandList::ResourceBarrier(D3D12_RESOURCE_BARRIER* barrier)
	{
		commandList->ResourceBarrier(1, barrier);
	}

	void CommandList::SetRenderTargets(Ref<D3D12SwapChain> swapchain, Ref<D3D12DepthBuffer> depthBuffer)
	{
		renderTarget = swapchain->GetCurrentRenderTargetDescriptor();
		this->depthBuffer = depthBuffer->GetDescriptorHandle();
		commandList->OMSetRenderTargets(1, &renderTarget, FALSE, &this->depthBuffer);
	}

	void CommandList::ClearRenderTargetView(const float* color)
	{
		commandList->ClearRenderTargetView(renderTarget, color, 0, nullptr);
	}

	void CommandList::ClearDepthStencilView(float depth, uint8_t stencil)
	{
		commandList->ClearDepthStencilView(depthBuffer, D3D12_CLEAR_FLAG_DEPTH, depth, stencil, 0, nullptr);
	}

	void CommandList::Close()
	{
		assert(isBeingRecorded);

		isBeingRecorded = false;

		DX_API("Failed to close command list")
			commandList->Close();
	}

	bool CommandList::IsRecording()
	{
		return this->isBeingRecorded;
	}

	void CommandList::DrawMesh(const std::shared_ptr<Assets::Mesh>& mesh)
	{
		auto index = std::dynamic_pointer_cast<D3D12IndexBuffer>(mesh->index_buffer);
		auto vert = std::dynamic_pointer_cast<D3D12VertexBuffer>(mesh->vertex_buffer);
		
		commandList->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		commandList->IASetIndexBuffer(&index->GetBufferView());
		commandList->IASetVertexBuffers(0, 1, &vert->GetBufferView());
		commandList->DrawIndexedInstanced(index->GetCount(), 1, 0, 0, 0);
	}

	void CommandList::BindConstantBuffer(const Ref<ConstantBuffer>& buffer, int registerIndex)
	{
		DX12ConstantBuffer* dx12_buffer = (DX12ConstantBuffer*)buffer->GetImpl().get();
		//Ref<DX12ConstantBuffer> dx12_buffer = std::dynamic_pointer_cast<D3D12::DX12ConstantBuffer>(buffer->GetImpl());
		commandList->SetGraphicsRootConstantBufferView(registerIndex, dx12_buffer->GetGPUVirtualAddress());
	}

	void CommandList::BindConstantBuffer(const ConstantBuffer& buffer, int registerIndex)
	{
		DX12ConstantBuffer* dx12_buffer = (DX12ConstantBuffer*)buffer.GetImpl().get();
		//Ref<DX12ConstantBuffer> dx12_buffer = std::dynamic_pointer_cast<D3D12::DX12ConstantBuffer>(buffer.GetImpl());
		commandList->SetGraphicsRootConstantBufferView(registerIndex, dx12_buffer->GetGPUVirtualAddress());
	}
	
	void CommandList::BindDescriptorTableBuffer(const CD3DX12_GPU_DESCRIPTOR_HANDLE& handle, int registerIndex)
	{
		D3D12_GPU_DESCRIPTOR_HANDLE h = handle;
		commandList->SetGraphicsRootDescriptorTable(registerIndex, h);
	}

	void CommandList::SetDescriptorHeaps(int count, ID3D12DescriptorHeap* const* descriptorHeaps)
	{
		commandList->SetDescriptorHeaps(count,descriptorHeaps);
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

		commandList->SetDescriptorHeaps(numDescriptorHeaps, descriptorHeaps);
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

	void CommandList::SetConstantBufferView(uint32_t rootParameterIndex,
		uint32_t descriptorOffset,
		const ConstantBuffer& resource,
		const D3D12_SHADER_RESOURCE_VIEW_DESC* srv)
	{
		m_DynamicDescriptorHeap[D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV]->StageDescriptors(rootParameterIndex, descriptorOffset, 1, resource.Get(srv));

		TrackResource(resource);
	}

	void CommandList::CopyTextureRegion(CD3DX12_TEXTURE_COPY_LOCATION* from, CD3DX12_TEXTURE_COPY_LOCATION* to)
	{
		commandList->CopyTextureRegion(to, 0, 0, 0, from, nullptr);
	}
}
