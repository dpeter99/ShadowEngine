#pragma once

/**
 *  @file Resource.h
 *  @date October 24, 2018
 *  @author Jeremiah van Oosten
 *
 *  @brief A wrapper for a DX12 resource. This provides a base class for all 
 *  other resource types (Buffers & Textures).
 */

#include "../Common.h"
#include <wrl.h>

#include <string>
#include "Platform/D3D12/D3D12IUploadable.h"

namespace ShadowEngine::Rendering::D3D12 {

	/// <summary>
	/// Represents a Buffer
	/// </summary>
	///
	/// Represents any resource in a committed resource heap on the GPU
	/// We inherit from this in:
	///  - ConstantBuffers
	///  - Textures
	class Resource : public D3D12IUploadable
	{
	protected:
		/// <summary>
		/// The actual underlying D3D12 resource on the GPU side
		/// </summary>
		Microsoft::WRL::ComPtr<ID3D12Resource> m_d3d12Resource;

		D3D12_FEATURE_DATA_FORMAT_SUPPORT m_FormatSupport;
		std::unique_ptr<D3D12_CLEAR_VALUE> m_d3d12ClearValue;
		std::wstring m_ResourceName;

		size_t m_bufferSize;

	public:
		
		explicit Resource(const std::wstring& name = L"");

		/// <summary>
		/// Creates a GPU side resource with the given parameters
		/// </summary>
		/// <param name="resourceDesc">The descriptor to use for the creating of the resource</param>
		/// <param name="clearValue">The clear value to use for the resource</param>
		/// <param name="name">The debug name to assign for this resource</param>
		explicit Resource(const D3D12_RESOURCE_DESC& resourceDesc,
			const D3D12_CLEAR_VALUE* clearValue = nullptr,
			const std::wstring& name = L"");

		/// <summary>
		/// Assumes ownership of the given resource
		/// </summary>
		/// <param name="resource">The resource to encapsulate</param>
		/// <param name="name">The debug name to assign to this resource</param>
		explicit Resource(Microsoft::WRL::ComPtr<ID3D12Resource> resource, const std::wstring& name = L"");

		Resource(const Resource& copy);
		Resource(Resource&& copy);
			
		Resource& operator=(const Resource& other);
		Resource& operator=(Resource&& other) noexcept;

		virtual ~Resource();

		/// <summary>
		/// Creates the underlying ID3D12Resource and assigns it to this instance
		/// </summary>
		/// <param name="resourceDesc">The descriptor to use for the creating of the resource</param>
		/// <param name="name">The debug name to assign for this resource</param>
		void SetupResource(const D3D12_RESOURCE_DESC& resourceDesc, const std::wstring& name);
		
		/// <summary>
		/// Check to see if the underlying resource is valid.
		/// </summary>
		/// <returns>Returns true if the resource is valid</returns>
		bool IsValid() const
		{
			return (m_d3d12Resource != nullptr);
		}

		/// <summary>
		/// Get access to the underlying D3D12 resource
		/// </summary>
		/// <returns>Returns with the ComPtr of the underlying ID3D12Resource instance</returns>
		com_ptr<ID3D12Resource> GetD3D12Resource() const
		{
			return m_d3d12Resource;
		}

		D3D12_RESOURCE_DESC GetD3D12ResourceDesc() const
		{
			D3D12_RESOURCE_DESC resDesc = {};
			if (m_d3d12Resource)
			{
				resDesc = m_d3d12Resource->GetDesc();
			}

			return resDesc;
		}

		// Replace the D3D12 resource
		// Should only be called by the CommandList.
		virtual void SetD3D12Resource(Microsoft::WRL::ComPtr<ID3D12Resource> d3d12Resource,
			const D3D12_CLEAR_VALUE* clearValue = nullptr);

		/**
		 * Get the SRV for a resource.
		 *
		 * @param srvDesc The description of the SRV to return. The default is nullptr
		 * which returns the default SRV for the resource (the SRV that is created when no
		 * description is provided.
		 */
		virtual D3D12_CPU_DESCRIPTOR_HANDLE GetShaderResourceView(const D3D12_SHADER_RESOURCE_VIEW_DESC* srvDesc = nullptr) const = 0;

		/**
		 * Get the UAV for a (sub)resource.
		 *
		 * @param uavDesc The description of the UAV to return.
		 */
		virtual D3D12_CPU_DESCRIPTOR_HANDLE GetUnorderedAccessView(const D3D12_UNORDERED_ACCESS_VIEW_DESC* uavDesc = nullptr) const = 0;

		/**
		 * Set the name of the resource. Useful for debugging purposes.
		 * The name of the resource will persist if the underlying D3D12 resource is
		 * replaced with SetD3D12Resource.
		 */
		void SetName(const std::wstring& name);

		/**
		 * Release the underlying resource.
		 * This is useful for swap chain resizing.
		 */
		virtual void Reset();

		/**
		 * Check if the resource format supports a specific feature.
		 */
		bool CheckFormatSupport(D3D12_FORMAT_SUPPORT1 formatSupport) const;
		bool CheckFormatSupport(D3D12_FORMAT_SUPPORT2 formatSupport) const;


	private:
		// Check the format support and populate the m_FormatSupport structure.
		void CheckFeatureSupport();
};

}

/*
 *  Copyright(c) 2018 Jeremiah van Oosten
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files(the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions :
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 *  IN THE SOFTWARE.
 */