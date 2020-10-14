#pragma once
#include "D3D12IUploadable.h"
#include "Buffers/Buffer.h"
#include "ShadowRenderer/Buffer.h"
#include "Platform/D3D12/Common.h"

namespace ShadowEngine::Rendering::D3D12 {


	/// <summary>
	/// Vertex Buffer holding vertices for Dx12.
	/// This holds the vertex buffer and the buffer descriptor as well
	/// </summary>
	class D3D12VertexBuffer : public VertexBuffer//, Buffer
	{
		
	public:

		/// <summary>
		/// Constructor for Dx12 Vertex Buffer
		/// </summary>
		/// <param name="vertices">The vertex data for this buffer to store</param>
		/// <param name="size">The size of the data (total length in bites)</param>
		/// <param name="name">The debug name for this Vertex Buffer</param>
		D3D12VertexBuffer(void* vertices, uint32_t size, const std::wstring& name = L"");
		
		/// <summary>
		/// Destructor..
		/// </summary>
		virtual ~D3D12VertexBuffer();

		const BufferLayout& GetLayout() const override { return m_Layout; }
		void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }

		/**
		 * Returns the buffer view to this vertex buffer.
		 * It returns a D3D12_VERTEX_BUFFER_VIEW struct witch is the Dx12 type for Vertex buffer views
		 *
		 * \brief Returns the Buffer View
		 * \return Buffer view returned
		 */
		const D3D12_VERTEX_BUFFER_VIEW& GetBufferView() const { return vertexBufferView; }
		
		//void RecordTransfer(Ref<D3D12::CommandList> cmd) override;
		//void FinishedUploading() override;;

	private:

		com_ptr<ID3D12Resource> uploadBuffer;
		
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
