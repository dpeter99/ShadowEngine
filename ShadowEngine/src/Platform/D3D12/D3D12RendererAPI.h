#pragma once
#include "ShadowRenderer/RendererAPI.h"

#include "Common.h"
#include "Platform/D3D12/D3D12Context.h"
#include "D3D12CommandQueue.h"
#include "D3D12SwapChain.h"
#include "D3D12Fence.h"
#include "D3D12CommandList.h"


namespace ShadowEngine::Rendering::D3D12 {

	class D3D12RendererAPI : public RendererAPI
	{
	public:
		/**
		 * \brief The dx12 device being used
		 */
		static com_ptr<ID3D12Device> device;
		/**
		 * \brief Context for renderering
		 */
		static ShadowEngine::Ref<D3D12::D3D12Context> ctx;

		
		/**
		 * \brief The default layout of the meshes being used
		 * TODO: Move this to global Renderer
		 */
		static BufferLayout input_layout;
	public:
		/**
		 * \brief The Graphics command queue
		 */
		Ref<D3D12::D3D12CommandQueue> command_queue;

		
		/**
		 * \brief The command list used for recording render commands
		 */
		Ref<D3D12::D3D12CommandList> command_list;

		
		/**
		 * \brief Swapchain of the render targets
		 */
		Ref<D3D12::D3D12SwapChain> swap_chain;

		/**
		 * \brief The depth buffer used
		 */
		Ref<D3D12::D3D12DepthBuffer> depth_buffer;

		D3D12_VIEWPORT viewPort;
		D3D12_RECT scissorRect;

		float aspectRatio;
		
		//Fence stuff
		//TODO: abstract these
		Ref<D3D12::D3D12Fence> fence;
		HANDLE fenceEvent;
		unsigned long long fenceValue;
		unsigned int frameIndex;
		
		virtual void Init(ShadowEngine::Ref<GraphicsContext> ctx) override;

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
		
		void StartFrame() override;
		void EndFrame() override;
		
		void WaitForPreviousFrame();
	};
}
