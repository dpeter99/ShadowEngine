#pragma once
#include "ShadowRenderer/CommandList.h"
#include "Common.h"
#include "D3D12DepthBuffer.h"
#include "ShadowRenderer/Shader.h"
#include <memory>
#include "D3D12Shader.h"
#include "ShadowAsset/Assets/Mesh.h"
#include "ShadowRenderer/ConstantBuffer.h"
#include <memory>
#include "D3D12DescriptorHeap.h"

namespace ShadowEngine::Rendering::D3D12 {
	class D3D12SwapChain;

	/**
	 * \brief A list of commands
	 * Used to record graphics/compute commands and than submit them at once
	 */
	class D3D12CommandList
	{
		com_ptr<ID3D12CommandAllocator> commandAllocator;
		com_ptr<ID3D12GraphicsCommandList> commandList;

		D3D12_CPU_DESCRIPTOR_HANDLE renderTarget;
		D3D12_CPU_DESCRIPTOR_HANDLE depthBuffer;

		bool isBeingRecorded;
	public:
		D3D12CommandList(D3D12_COMMAND_LIST_TYPE type = D3D12_COMMAND_LIST_TYPE_DIRECT);

		/**
		 * \brief 
		 * \return The dx12 command list
		 */
		com_ptr<ID3D12GraphicsCommandList> GetCommandList() { return commandList; }

		
		/**
		 * \brief Binds a new shader to the command list to use
		 * \param shader The shader to be used
		 * 
		 */
		void UseShader(const Ref<D3D12Shader>& shader);
		
		/**
		 * \brief Resets the Command List
		 * Should only be used when we are sure it is not in use
		 */
		void Reset();

		void StartRecording();
		
		void SetViewports(D3D12_VIEWPORT viewPort);

		void SetScissorRects(D3D12_RECT scissorRect);

		/**
		 * \brief Adds a new resource barrier to the command list
		 * \param barrier The barrier to use
		 * Used to wait for a resource transition to happen (eg. rendertarget is available)
		 */
		void ResourceBarrier(D3D12_RESOURCE_BARRIER* barrier);

		/**
		 * \brief Set the render targets used in this command list
		 * \param swapchain The swap chain to get the render target form
		 * \param depthBuffer The depth buffer to use
		 */
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

		void D3D12CommandList::SetDescriptorHeaps(int count, ID3D12DescriptorHeap* const* descriptorHeaps);
		void D3D12CommandList::SetDescriptorHeaps(std::vector<Ref<D3D12DescriptorHeap>> descriptorHeaps);
		
		void Close();

		bool IsRecording();
	};

}
