#pragma once
//#include "ShadowRenderer/CommandList.h"
#include "Common.h"
#include "D3D12DepthBuffer.h"
#include "ShadowRenderer/Shader.h"
#include "Shader/DX12Shader.h"
#include "Assets/Assets/Mesh.h"
#include "ShadowRenderer/ConstantBuffer.h"
#include "D3D12DescriptorHeap.h"
#include <Platform\D3D12\Descriptors\DynamicDescriptorHeap.h>
#include "Buffers/Buffer.h"
#include "Resource/ResourceStateTracker.h"
#include "Buffers/UploadBuffer.h"

#include "CommandAllocator/CommandAllocatorPool.h"

namespace ShadowEngine::Rendering::D3D12 {
	class Texture;
	class D3D12SwapChain;

	/// <summary>
	/// Wrapper for the ID3D12GraphicsCommandList class
	/// </summary>
	/// Contains and manages a ``ID3D12CommandAllocator`` and ``ID3D12GraphicsCommandList``.
	/// It is used for recording commands and than submitting them to a <see cref="CommandQueue"/>.
	class CommandList
	{
		D3D12_COMMAND_LIST_TYPE type;
		
		/// <summary>
		/// The command allocator that we are allocating out of
		/// </summary>
		/// The command allocator is responsible for allocating the memory for the CommandLists
		Ref<CommandAllocator> commandAllocator;
		
		/// <summary>
		/// The encapsulated CommandList
		/// </summary>
		/// This is the DX12 class that we are making the calls to
		com_ptr<ID3D12GraphicsCommandList> m_commandList;

		
		/// <summary>
		/// The last set render target for this queue
		/// </summary>
		D3D12_CPU_DESCRIPTOR_HANDLE renderTarget;
		
		/// <summary>
		/// The last set depth buffer for this queue
		/// </summary>
		D3D12_CPU_DESCRIPTOR_HANDLE depthBuffer;

		bool isBeingRecorded;

		/// <summary>
		/// Resource state tracker is used by the command list to track (per command list)
		/// the current state of a resource. The resource state tracker also tracks the
		/// global state of a resource (with it's static methods) in order to minimize resource state transitions.
		/// </summary>
		std::unique_ptr<ResourceStateTracker> m_ResourceStateTracker;

		using TrackedObjects = std::vector < Microsoft::WRL::ComPtr<ID3D12Object> >;
		
		/// <summary>
		/// A list of "in-flight" object to make sure they are not deleted before the command list finishes
		/// </summary>
		/// Objects that are being tracked by a command list that is "in-flight" on 
		///	the command-queue and cannot be deleted. To ensure objects are not deleted
		///	until the command list is finished executing, a reference to the object
		///	is stored. The referenced objects are released when the command list is 
		/// reset.
		TrackedObjects m_TrackedObjects;
		
		/// <summary>
		/// The dynamic descriptor heap allows for descriptors to be staged before
		/// being committed to the command list. Dynamic descriptors need to be
		/// committed before a Draw or Dispatch.
		/// </summary>
		std::unique_ptr<DynamicDescriptorHeap> m_DynamicDescriptorHeap[D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES];

		/// <summary>
		/// The currently bound descriptor heaps. Only bind new one if it is not currently bound
		/// </summary>
		/// Keeps track of the currently bound descriptor heaps. Only change descriptor
		/// heaps if they are different than the currently bound descriptor heaps.
		ID3D12DescriptorHeap* m_DescriptorHeaps[D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES] = {};

		// Resource created in an upload heap. Useful for drawing of dynamic geometry
		// or for uploading constant buffer data that changes every draw call.
		std::unique_ptr<UploadBuffer> m_UploadBuffer;
	public:
		
		CommandList(D3D12_COMMAND_LIST_TYPE type = D3D12_COMMAND_LIST_TYPE_DIRECT);

		void SetName(std::wstring name);

		
		/// <summary>
		/// Returns the underlying command list.
		/// </summary>
		/// <returns>The underlying command list.</returns>
		com_ptr<ID3D12GraphicsCommandList> GetCommandList() { return m_commandList; }


		/// <summary>
		/// Resets the Command List
		/// </summary>
		/// <param name="frame">The frame that we are starting</param>
		///
		/// When this is called an new allocator is requested form the pool with the frame
		void Reset(uint64_t frame, Ref<D3D12CommandQueue> queue);

		void StartRecording();

		//#################################################
		// Graphics Commands
		//#################################################
		
#pragma region View_port_and_scissor
		
		void SetViewports(D3D12_VIEWPORT viewPort);

		void SetScissorRects(D3D12_RECT scissorRect);

#pragma endregion

#pragma region Render Target
		
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

#pragma endregion

		
		/// <summary>
		/// Adds a new resource barrier to the command list
		/// </summary>
		/// Used to wait for a resource transition to happen (eg. render target is available)
		/// 
		/// <param name="barrier">The barrier to use</param>
		void ResourceBarrier(D3D12_RESOURCE_BARRIER* barrier);

		/// <summary>
		/// (V2) Transition a resource to a particular state.
		/// </summary>
		/// <param name="resource">The resource to transition.</param>
		/// <param name="stateAfter">The state to transition the resource to. The before state is resolved by the resource state tracker.</param>
		/// <param name="subresource">The subresource to transition. By default, this is D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES which indicates that all subresources are transitioned to the same state.</param>
		/// <param name="flushBarriers">Force flush any barriers. Resource barriers need to be flushed before a command (draw, dispatch, or copy) that expects the resource to be in a particular state can run.</param>
		void TransitionBarrier(com_ptr<ID3D12Resource> resource, D3D12_RESOURCE_STATES stateAfter, UINT subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES, bool flushBarriers = false);

		/// <summary>
		/// (V2) Transition a resource to a particular state.
		/// </summary>
		/// <param name="resource">The resource to transition.</param>
		/// <param name="stateAfter">The state to transition the resource to. The before state is resolved by the resource state tracker.</param>
		/// <param name="subresource">The subresource to transition. By default, this is D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES which indicates that all subresources are transitioned to the same state.</param>
		/// <param name="flushBarriers">Force flush any barriers. Resource barriers need to be flushed before a command (draw, dispatch, or copy) that expects the resource to be in a particular state can run.</param>
		void TransitionBarrier(const Resource& resource, D3D12_RESOURCE_STATES stateAfter, UINT subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES, bool flushBarriers = false);

		/// <summary>
		/// Flush any barriers that have been pushed to the command list.
		/// </summary>
		void FlushResourceBarriers();
		

		/// <summary>
		/// Uploads the given data to the specified buffer.
		/// </summary>
		/// <param name="buffer">The buffer to upload the data to</param>
		/// <param name="numElements">Number of elements that the data has</param>
		/// <param name="elementSize">The size of a single element that the data has</param>
		/// <param name="bufferData">Pointer to the memory location of the data</param>
		/// <param name="flags">Flags to use</param>
		///
		///	<example>
		///	A example usage of this is uploading a single data
		///	<code>		
		///	Data* data = new Data;
		///	UploadToBuffer(buffer, 1, sizeof(Type), data, D3D12_RESOURCE_FLAG_NONE)
		///	</code>
		///	</example>
		/// 
		void UploadToBuffer(Buffer& buffer, size_t numElements, size_t elementSize, const void* bufferData,
		                D3D12_RESOURCE_FLAGS flags);


		/**
		* Copy subresource data to a texture.
		*/
		void CopyTextureSubresource(Texture& destination, uint32_t firstSubresource, uint32_t numSubresources, D3D12_SUBRESOURCE_DATA* subresourceData);
		
		
		void DrawMesh(const std::shared_ptr<Assets::Mesh>& mesh);

		void BindConstantBuffer [[deprecated]]  (const Ref<ConstantBuffer>& buffer, int materialSlotIndex);
		void BindConstantBuffer [[deprecated]]  (const ConstantBuffer& buffer, int registerIndex);
		void BindDescriptorTableBuffer [[deprecated]] (const CD3DX12_GPU_DESCRIPTOR_HANDLE& handle, int registerIndex);

		/**
		* Set a dynamic constant buffer data to an inline descriptor in the root
		* signature.
		*/
		void SetGraphicsDynamicConstantBuffer(uint32_t rootParameterIndex, size_t sizeInBytes, const void* bufferData);
		template<typename T>
		void SetGraphicsDynamicConstantBuffer(uint32_t rootParameterIndex, const T& data)
		{
			SetGraphicsDynamicConstantBuffer(rootParameterIndex, sizeof(T), &data);
		}

		
		

		void TrackResource(Microsoft::WRL::ComPtr<ID3D12Object> object);
		void TrackResource(const Resource& res);
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


		/**
		 * \brief Binds a new shader to the command list to use
		 * \param shader The shader to be used
		 *
		 */
		void UseShader(const Ref<DX12Shader>& shader);

		/// <summary>
		/// Sets a resource as the SRV in the specified place
		/// </summary>
		/// <param name="rootParameterIndex">The index of the descriptor table to set this in</param>
		/// <param name="descriptorOffset">The index in the descriptor table to place the view</param>
		/// <param name="resource">The resource to bind</param>
		/// <param name="stateAfter">The state that we want this to be in</param>
		/// <param name="firstSubresource">The first subresources index</param>
		/// <param name="numSubresources"Number of subresources this has></param>
		/// <param name="srv">The SRV desc to use. If nullptr than the default one will be used</param>
		void SetShaderResourceView(
			uint32_t rootParameterIndex,
			uint32_t descriptorOffset,
			const Resource& resource,
			D3D12_RESOURCE_STATES stateAfter = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE |
			D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE,
			UINT firstSubresource = 0,
			UINT numSubresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
			const D3D12_SHADER_RESOURCE_VIEW_DESC* srv = nullptr
		);

		
		void CommandList::SetShaderConstandBufferView(
			uint32_t rootParameterIndex,
			uint32_t descriptorOffset,
			const Buffer& resource,
			UINT firstSubresource = 0,
			UINT numSubresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
			const D3D12_CONSTANT_BUFFER_VIEW_DESC* cbv = nullptr);

		
		
		void Close();

		bool IsRecording();
	};

}
