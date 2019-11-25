#include "shpch.h"
#include "D3D12CommandList.h"
#include "D3D12RendererAPI.h"
#include "D3D12Shader.h"
#include "D3D12Buffers.h"
#include "D3D12ConstantBuffer.h"

namespace ShadowEngine::Rendering::D3D12 {

	D3D12CommandList::D3D12CommandList(D3D12_COMMAND_LIST_TYPE type)
	{
		DX_API("Failed to create command allocator")
			D3D12RendererAPI::device->CreateCommandAllocator(type, IID_PPV_ARGS(commandAllocator.GetAddressOf()));

		DX_API("Failed to greate graphics command list")
			D3D12RendererAPI::device->CreateCommandList(0, type, commandAllocator.Get(), nullptr, IID_PPV_ARGS(commandList.GetAddressOf()));

		commandList->Close();

		isBeingRecorded = false;
	}

	void D3D12CommandList::UseShader(const Ref<D3D12Shader>& shader)
	{
		commandList->SetPipelineState(shader->GetPipelineState().Get());
		commandList->SetGraphicsRootSignature(shader->GetRootSignature().Get());
	}

	void D3D12CommandList::Reset()
	{
		//if (isBeingRecorded)
			isBeingRecorded = true;
		
		commandAllocator->Reset();
		commandList->Reset(commandAllocator.Get(), nullptr);
	}

	void D3D12CommandList::StartRecording [[deprecated]] ()
	{
		SH_CORE_ASSERT(isBeingRecorded, "Command list is already recording");
		
		if(!isBeingRecorded)
		isBeingRecorded = true;
			
	}

	void D3D12CommandList::SetViewports(D3D12_VIEWPORT viewPort)
	{
		commandList->RSSetViewports(1, &viewPort);
	}

	void D3D12CommandList::SetScissorRects(D3D12_RECT scissorRect)
	{
		commandList->RSSetScissorRects(1, &scissorRect);
	}

	void D3D12CommandList::ResourceBarrier(D3D12_RESOURCE_BARRIER* barrier)
	{
		commandList->ResourceBarrier(1, barrier);
	}

	void D3D12CommandList::SetRenderTargets(Ref<D3D12SwapChain> swapchain, Ref<D3D12DepthBuffer> depthBuffer)
	{
		renderTarget = swapchain->GetCurrentRenderTargetDescriptor();
		this->depthBuffer = depthBuffer->GetDescriptorHandle();
		commandList->OMSetRenderTargets(1, &renderTarget, FALSE, &this->depthBuffer);
	}

	void D3D12CommandList::ClearRenderTargetView(const float* color)
	{
		commandList->ClearRenderTargetView(renderTarget, color, 0, nullptr);
	}

	void D3D12CommandList::ClearDepthStencilView(float depth, uint8_t stencil)
	{
		commandList->ClearDepthStencilView(depthBuffer, D3D12_CLEAR_FLAG_DEPTH, depth, stencil, 0, nullptr);
	}

	void D3D12CommandList::Close()
	{
		assert(isBeingRecorded);

		isBeingRecorded = false;

		DX_API("Failed to close command list")
			commandList->Close();
	}

	bool D3D12CommandList::IsRecording()
	{
		return this->isBeingRecorded;
	}

	void D3D12CommandList::DrawMesh(const std::shared_ptr<Assets::Mesh>& mesh)
	{
		auto index = std::dynamic_pointer_cast<D3D12IndexBuffer>(mesh->index_buffer);
		auto vert = std::dynamic_pointer_cast<D3D12VertexBuffer>(mesh->vertex_buffer);
		
		commandList->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		commandList->IASetIndexBuffer(&index->GetBufferView());
		commandList->IASetVertexBuffers(0, 1, &vert->GetBufferView());
		commandList->DrawIndexedInstanced(index->GetCount(), 1, 0, 0, 0);
	}

	void D3D12CommandList::BindConstantBuffer(const Ref<ConstantBuffer>& buffer, int registerIndex)
	{
		Ref<D3D12ConstantBuffer> dx12_buffer = std::dynamic_pointer_cast<D3D12::D3D12ConstantBuffer>(buffer->GetImpl());
		commandList->SetGraphicsRootConstantBufferView(registerIndex, dx12_buffer->GetGPUVirtualAddress());
	}

	void D3D12CommandList::BindConstantBuffer(const ConstantBuffer& buffer, int registerIndex)
	{
		Ref<D3D12ConstantBuffer> dx12_buffer = std::dynamic_pointer_cast<D3D12::D3D12ConstantBuffer>(buffer.GetImpl());
		commandList->SetGraphicsRootConstantBufferView(registerIndex, dx12_buffer->GetGPUVirtualAddress());
	}
	void D3D12CommandList::CopyTextureRegion(CD3DX12_TEXTURE_COPY_LOCATION* from, CD3DX12_TEXTURE_COPY_LOCATION* to)
	{
		commandList->CopyTextureRegion(to, 0, 0, 0, from, nullptr);
	}
}
