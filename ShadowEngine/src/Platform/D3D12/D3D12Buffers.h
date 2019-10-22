#pragma once
#include "ShadowRenderer/Buffer.h"
#include "Platform/D3D12/Common.h"

namespace ShadowEngine::Rendering::D3D12 {

	/**
	 * \brief Vertex Buffer holding vertices in a Dx12 way
	 * This hold the vertex buffer and the buffer view for it as well
	 */
	class D3D12VertexBuffer : public VertexBuffer
	{
	public:
		D3D12VertexBuffer(void* vertices, uint32_t size);
		virtual ~D3D12VertexBuffer();

		virtual const ShadowEngine::Rendering::BufferLayout& GetLayout() const override { return m_Layout; }
		virtual void SetLayout(const ShadowEngine::Rendering::BufferLayout& layout) override { m_Layout = layout; }

		/**
		 * Returns the buffer view to this vertex buffer.
		 * It returns a D3D12_VERTEX_BUFFER_VIEW struct witch is the Dx12 type for Vertex buffer views
		 *
		 * \brief Returns the Buffer View
		 * \return Buffer view returned
		 */
		const D3D12_VERTEX_BUFFER_VIEW& GetBufferView() const { return vertexBufferView; };
	private:
		com_ptr<ID3D12Resource> vertexBuffer;
		D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
		ShadowEngine::Rendering::BufferLayout m_Layout;
	};

	/**
	 * \brief Index Buffer holding an index array in a Dx12 way
	 * This hold the index buffer and the buffer view for it as well
	 */
	class D3D12IndexBuffer : public IndexBuffer
	{
	public:
		D3D12IndexBuffer(void* vertices, uint32_t size);
		virtual ~D3D12IndexBuffer();

	

		virtual uint32_t GetCount() const { return m_Count; }
		
		/**
		 * Returns the buffer view to this index buffer.
		 * It returns a D3D12_INDEX_BUFFER_VIEW struct witch is the Dx12 type for Index buffer views
		 * 
		 * \brief Returns the Buffer View
		 * \return Buffer view returned
		 */
		const D3D12_INDEX_BUFFER_VIEW& GetBufferView() const { return indexBufferView; };
		
	private:
		uint32_t m_Count;
		
		com_ptr<ID3D12Resource> indexBuffer;
		D3D12_INDEX_BUFFER_VIEW indexBufferView{};
		
	};
}
