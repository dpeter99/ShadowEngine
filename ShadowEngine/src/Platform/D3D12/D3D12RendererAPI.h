#pragma once
#include "ShadowRenderer/RendererAPI.h"

#include "Common.h"
#include "Platform/D3D12/D3D12Context.h"
#include "D3D12CommandQueue.h"
#include "D3D12SwapChain.h"
#include "D3D12Fence.h"
#include "D3D12CommandList.h"
#include "ShadowAsset/Assets/Mesh.h"
#include "ShadowRenderer/Shader.h"
#include "ShadowAsset/Assets/Material.h"


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
		//unsigned int frameIndex;
		
		virtual void Init(ShadowEngine::Ref<GraphicsContext> ctx) override;

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void Draw(const Ref<Assets::Mesh> mesh, const Ref<Assets::Material> shader, const glm::mat4& transform = glm::mat4(1.0f)) override;

		void Draw(const std::shared_ptr<Assets::Mesh>& mesh, const std::shared_ptr<Assets::Material>& shader, Ref<ConstantBuffer> materialData) override;
		
		void StartFrame() override;
		void EndFrame() override;
		
		void WaitForPreviousFrame();
		
	};
}
