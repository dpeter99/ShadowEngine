#pragma once
#include "ShadowRenderer/RendererAPI.h"

#include "Common.h"
#include "Platform/D3D12/D3D12Context.h"
#include "D3D12CommandQueue.h"
#include "D3D12SwapChain.h"
#include "D3D12Fence.h"
#include "D3D12DepthStencilBuffer.h"


namespace ShadowEngine::Rendering::D3D12 {

	class D3D12RendererAPI : public RendererAPI
	{
	public:
		static com_ptr<ID3D12Device> device;
		static ShadowEngine::Ref<D3D12::D3D12Context> ctx;

		static BufferLayout input_layout;
	public:
		Ref<D3D12::D3D12CommandQueue> command_queue;
		Ref<D3D12::D3D12SwapChain> swap_chain;
		
		Ref<D3D12::D3D12Fence> fence;
		HANDLE fenceEvent;
		unsigned long long fenceValue;
		unsigned int frameIndex;

		Ref<D3D12DescriptorHeap> dsvHeap;
		Ref<D3D12::D3D12DepthStencilBuffer> depthBuffer;
		
		virtual void Init(ShadowEngine::Ref<GraphicsContext> ctx) override;

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}
