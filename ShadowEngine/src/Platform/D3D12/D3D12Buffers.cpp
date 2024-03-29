#include "shpch.h"
#include "D3D12Buffers.h"
#include "Common.h"
#include "D3D12RendererAPI.h"
#include "ShadowRenderer/DataStructs.h"

namespace ShadowEngine::Rendering::D3D12 {

	/**
	 * \brief Constructor for Dx12 Vertex Buffer
	 * \param vertices The vertex data for this buffer to store
	 * \param size the size of the data (total length in bites)
	 */
	D3D12VertexBuffer::D3D12VertexBuffer(void* vertices, uint32_t size)
	{
		//Id of the vertex buffer
		//TODO: Replace with obj id form SHObject
		static int id = 0;
		
		//Allocate the needed memory
		DX_API("Failed to create vertex buffer (IndexedGeometry)")
			ShadowEngine::Rendering::D3D12::D3D12RendererAPI::device->CreateCommittedResource(
				&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
				D3D12_HEAP_FLAG_NONE,
				&CD3DX12_RESOURCE_DESC::Buffer(size),
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(vertexBuffer.GetAddressOf()));

		//Get the CPU RAM mapped to the resource
		CD3DX12_RANGE range{ 0,0 };
		void* mappedPtr;
		DX_API("Failed to map vertex buffer (IndexedGeometry)")
			vertexBuffer->Map(0, &range, &mappedPtr);

		//Copy the data to the ram
		memcpy(mappedPtr, vertices, size);
		vertexBuffer->Unmap(0, nullptr);

		//Name for debugging
		DX_API("Failed to set name for vertex buffer (IndexedGeometry)")
			vertexBuffer->SetName(WFormat(L"VertexBuffer#%d", id++).c_str());

		
		vertexBufferView.BufferLocation = vertexBuffer->GetGPUVirtualAddress();
		vertexBufferView.SizeInBytes = size;
		vertexBufferView.StrideInBytes = sizeof(Vertex);
	}

	D3D12VertexBuffer::~D3D12VertexBuffer()
	{
		std::cout << "Vertex Buffer free";
	}

	/**
	 * \brief Constructor for Dx12 Index Buffer
	 * \param indexData The index data for this buffer to store
	 * \param size the size of the data (total length in bites)
	 */
	D3D12IndexBuffer::D3D12IndexBuffer(void* indexData, uint32_t size)
	{
		//Id of the vertex buffer
		//TODO: Replace with obj id form SHObject
		static int id = 0;
		
		DX_API("Failed to create index buffer (IndexedGeometry")
		D3D12RendererAPI::device->CreateCommittedResource(
				&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
				D3D12_HEAP_FLAG_NONE,
				&CD3DX12_RESOURCE_DESC::Buffer(size),
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(indexBuffer.GetAddressOf()));


		//Get the CPU RAM mapped to the resource
		CD3DX12_RANGE range{ 0,0 };
		void* mappedPtr;
		DX_API("Failed to map index buffer (IndexedGeometry")
			indexBuffer->Map(0, &range, &mappedPtr);

		memcpy(mappedPtr, indexData, size);
		indexBuffer->Unmap(0, nullptr);

		DX_API("Failed to set name for index buffer (IndexedGeometry)")
			indexBuffer->SetName(WFormat(L"IndexBuffer#%d", id++).c_str());

		indexBufferView.BufferLocation = indexBuffer->GetGPUVirtualAddress();
		//TODO: Ability to set index format
		indexBufferView.Format = DXGI_FORMAT_R32_UINT;
		indexBufferView.SizeInBytes = size;

		m_Count = (size / 4);

	}

	D3D12IndexBuffer::~D3D12IndexBuffer()
	{
		std::cout << "Index Buffer free";
	}
}
