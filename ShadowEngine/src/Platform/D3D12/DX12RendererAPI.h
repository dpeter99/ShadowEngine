#pragma once
#include "ShadowRenderer/RendererAPI.h"

#include "Common.h"
#include "Platform/D3D12/D3D12Context.h"
#include "D3D12CommandQueue.h"
#include "D3D12SwapChain.h"
#include "D3D12Fence.h"
#include "CommandList.h"
#include "Assets/Assets/Mesh.h"
#include "ShadowRenderer/Shader.h"
#include "Assets/Assets/Material.h"
#include "UploadManagger.h"
#include <Platform\D3D12\Descriptors\DescriptorAllocation.h>
#include <Platform\D3D12\Descriptors\DescriptorAllocator.h>

namespace ShadowEngine::Rendering::D3D12 {

	/// <summary>
	/// The DirectX12 Rendering back end
	/// </summary>
	/// 
	/// This is the rendering backend for DX12
	/// It implements the RenderingAPI interface and is the entry point for the renderer
	class DX12RendererAPI : public RendererAPI
	{
	public:		
		/// <summary>
		/// The dx12 device being used
		/// </summary>
		static com_ptr<ID3D12Device> device;

		/// <summary>
		/// Context for renderering
		/// </summary>
		static ShadowEngine::Ref<D3D12::D3D12Context> ctx;

		/// <summary>
		/// Singleton instance
		/// </summary>
		static DX12RendererAPI* Instance;

	public:
		
		/// <summary>
		/// The Graphics command queue
		/// </summary>
		/// All graphics commands are submitted to this queue, and it runs them in order of submission
		Ref<D3D12::D3D12CommandQueue> command_queue;


		Ref<CommandAllocatorPool> command_allocaotr_pool;
		
		/// <summary>
		/// The command list used for recording render commands for the graphics command queue
		/// </summary>
		/// This is the command list that is being written into while recording.
		/// This is always the current frame's list, it is reset at the end of the recording and assigned a new allocator
		Ref<D3D12::CommandList> command_list;

		uint64_t frame_index;
		
		/// <summary>
		/// The upload manager, it handles the uploads of resources
		/// </summary>
		/// This should be used trough the following methodes:
		///  - <see cref="UploadResource"/>
		/// The <see cref="StartResourceUpload"/> should only be called by the system
		Ref<UploadManagger> upload_managger;

		/// <summary>
		/// The descriptor heap allocators.
		/// </summary>
		/// This is a array of descriptor heap allocators that are responsible for managing the descriptors
		/// of each type
		///  - ``D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV``
		///  - ``D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER``
		///  - ``D3D12_DESCRIPTOR_HEAP_TYPE_RTV``
		///	 - ``D3D12_DESCRIPTOR_HEAP_TYPE_DSV``
		///
		///	 Currently ``D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES`` is 4
		std::unique_ptr<DescriptorAllocator> m_DescriptorAllocators[D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES];

		/// <summary>
		/// The Swapchain of the render targets
		/// </summary>
		Ref<D3D12::D3D12SwapChain> swap_chain;

		/// <summary>
		/// The depth buffer used
		/// </summary>
		Ref<D3D12::D3D12DepthBuffer> depth_buffer;

		D3D12_VIEWPORT viewPort;
		D3D12_RECT scissorRect;

		float aspectRatio;
		
		//Fence stuff
		//TODO: abstract these
		Ref<D3D12::D3D12Fence> fence;
		//HANDLE fenceEvent;
		//unsigned long long fenceValue;
		//unsigned int currentBackBufferIndex;

		//Ref<D3D12DescriptorHeap> descriptorHeap_SRV_CBV;

		
		
		Ref<ConstantBuffer> worldData;

		glm::vec4 clearColor;

	public:

		static DX12RendererAPI& Get() { return *Instance; }

		/// <summary>
		/// Sets up the renderer
		/// </summary>
		/// <param name="ctx">The Renderer context that is being used</param>
		virtual void Init(ShadowEngine::Ref<GraphicsContext> ctx) override;

		/// <summary>
		/// Starts a new frame for recording
		/// </summary>
		/// <param name="worldCB">The constant buffer containing the world data</param>
		/// The World data contains the camera position and matrix, the lights and other parameters that are the same for the whole scene
		void StartFrame(Ref<ConstantBuffer> worldCB, uint64_t frame) override;

		/// <summary>
		/// This ends the recording of the frame. It subbmits it and queues the swapchain swap
		/// </summary>
		void EndFrame() override;

		/// <summary>
		/// Sets the Clear color to be used when calling the next clear command
		/// </summary>
		/// <param name="color"></param>
		virtual void SetClearColor(const glm::vec4& color) override;

		/// <summary>
		/// Clears the currently bound render target with the clear color from <see cref="SetClearColor"/>
		/// </summary>
		virtual void Clear() override;

		
		/// <summary>
		/// Draws a mesh with the given parameters
		/// </summary>
		/// <param name="mesh">The mesh that we want to draw</param>
		/// <param name="shader">The sahder that should be used for it</param>
		/// <param name="materialData">Material data to be bound</param>
		virtual void Draw(const std::shared_ptr<Assets::Mesh>& mesh, const std::shared_ptr<Assets::Material>& shader,const ConstantBuffer& materialData) override;
		
		
		
		void UploadResource(Ref<D3D12IUploadable> resource);

		void UploadResource(D3D12IUploadable* resource);

		void StartResourceUpload() override;

		
		UINT GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE type) const;

		DescriptorAllocation AllocateDescriptors(D3D12_DESCRIPTOR_HEAP_TYPE type, uint32_t numDescriptors = 1);

		void ReleaseStaleDescriptors(uint64_t finishedFrame);

		com_ptr<ID3D12DescriptorHeap> CreateDescriptorHeap(UINT numDescriptors, D3D12_DESCRIPTOR_HEAP_TYPE type);

		//void WaitForPreviousFrame();
		
	};
}
