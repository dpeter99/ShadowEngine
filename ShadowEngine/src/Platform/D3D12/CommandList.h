#pragma once
#include "ShadowRenderer/CommandList.h"
#include "Common.h"
#include "D3D12DepthBuffer.h"
#include "ShadowRenderer/Shader.h"
#include "Shader/DX12Shader.h"
#include "ShadowAsset/Assets/Mesh.h"
#include "ShadowRenderer/ConstantBuffer.h"
#include "D3D12DescriptorHeap.h"
#include <Platform\D3D12\Descriptors\DynamicDescriptorHeap.h>

namespace ShadowEngine::Rendering::D3D12 {
	class D3D12SwapChain;

	/**
	 * \brief A list of commands
	 * Used to record graphics/compute commands and than submit them at once
	 */
	class CommandList
	{
		com_ptr<ID3D12CommandAllocator> commandAllocator;
		com_ptr<ID3D12GraphicsCommandList> commandList;

		D3D12_CPU_DESCRIPTOR_HANDLE renderTarget;
		D3D12_CPU_DESCRIPTOR_HANDLE depthBuffer;

		bool isBeingRecorded;

		/// <summary>
		/// The dynamic descriptor heap allows for descriptors to be staged before
		/// being committed to the command list. Dynamic descriptors need to be
		/// committed before a Draw or Dispatch.
		/// </summary>
		std::unique_ptr<DynamicDescriptorHeap> m_DynamicDescriptorHeap[D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES];

		/// <summary>
		/// Keep track of the currently bound descriptor heaps. Only change descriptor
		/// heaps if they are different than the currently bound descriptor heaps.
		/// </summary>
		ID3D12DescriptorHeap* m_DescriptorHeaps[D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES];
	public:
		CommandList(D3D12_COMMAND_LIST_TYPE type = D3D12_COMMAND_LIST_TYPE_DIRECT);

		/// <summary>
		/// Returns the underlying command list.
		/// </summary>
		/// <returns>The underlying command list.</returns>
		com_ptr<ID3D12GraphicsCommandList> GetCommandList() { return commandList; }


		/**
		 * \brief Binds a new shader to the command list to use
		 * \param shader The shader to be used
		 *
		 */
		void UseShader(const Ref<DX12Shader>& shader);

		/**
		 * \brief Resets the Command List
		 * Should only be used when we are sure it is not in use
		 */
		void Reset();

		void StartRecording();

		void SetViewports(D3D12_VIEWPORT viewPort);

		void SetScissorRects(D3D12_RECT scissorRect);

		/// <summary>
		/// Adds a new resource barrier to the command list
		/// </summary>
		/// <param name="barrier">The barrier to use</param>
		/// Used to wait for a resource transition to happen (eg. rendertarget is available)
		void ResourceBarrier(D3D12_RESOURCE_BARRIER* barrier);

		/// <summary>
		///  Sets the render targets used in this command list
		/// </summary>
		/// <param name="swapchain">The swap chain to get the render target form</param>
		/// <param name="depthBuffer">The depth buffer to use</param>
		void SetRenderTargets(
			Ref<D3D12SwapChain> swapchain,
			Ref<D3D12DepthBuffer> depthBuffer);

		void ClearRenderTargetView(const float* color);

		void ClearDepthStencilView(float depth, uint8_t stencil);

		void DrawMesh(const std::shared_ptr<Assets::Mesh>& mesh);

		void BindConstantBuffer(const Ref<ConstantBuffer>& buffer, int materialSlotIndex);
		void BindConstantBuffer(const ConstantBuffer& buffer, int registerIndex);
		void BindDescriptorTableBuffer(const CD3DX12_GPU_DESCRIPTOR_HANDLE& handle, int registerIndex);

		void CopyTextureRegion(CD3DX12_TEXTURE_COPY_LOCATION* from, CD3DX12_TEXTURE_COPY_LOCATION* to);

		void SetDescriptorHeaps [[deprecated]] (int count, ID3D12DescriptorHeap* const* descriptorHeaps);
		//void SetDescriptorHeaps(std::vector<Ref<D3D12DescriptorHeap>> descriptorHeaps);

		/// <summary>
		/// Set the currently bound descriptor heap.
		/// Should only be called by the DynamicDescriptorHeap class.
		/// </summary>
		/// <param name="heapType">The type of the heap that is being bound</param>
		/// <param name="heap">The actual heap pointer that should be bound</param>
		void SetDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType, ID3D12DescriptorHeap* heap);

		/// <summary>
		/// Binds the current descriptor heaps to the command list.
		/// </summary>
		/// Adds the bind calls for all the currently set descriptor heaps
		void BindDescriptorHeaps();

		void SetShaderResourceView(uint32_t rootParameterIndex, uint32_t descriptorOffset, const Resource& resource, D3D12_RESOURCE_STATES stateAfter, UINT firstSubresource, UINT numSubresources, const D3D12_SHADER_RESOURCE_VIEW_DESC* srv);

		void SetShaderConstandBufferDescriptor(uint32_t rootParameterIndex, uint32_t descriptorOffset, UINT firstSubresource, UINT numSubresources, const D3D12_GPU_DESCRIPTOR_HANDLE descriptor);

		void Close();

		bool IsRecording();
	};

}
