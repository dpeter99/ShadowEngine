#pragma once
#include "ShadowRenderer/Buffer.h"
#include "Platform/D3D12/Common.h"

namespace ShadowEngine::Rendering::D3D12 {

	class D3D12VertexBuffer : public VertexBuffer
	{
	public:
		D3D12VertexBuffer(void* vertices, uint32_t size);
		virtual ~D3D12VertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const ShadowEngine::Rendering::BufferLayout& GetLayout() const override { return m_Layout; }
		virtual void SetLayout(const ShadowEngine::Rendering::BufferLayout& layout) override { m_Layout = layout; }
	private:
		com_ptr<ID3D12Resource> vertexBuffer;
		D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
		ShadowEngine::Rendering::BufferLayout m_Layout;
	};

	class D3D12IndexBuffer : public IndexBuffer
	{
	public:
		D3D12IndexBuffer(void* vertices, uint32_t size);
		virtual ~D3D12IndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual uint32_t GetCount() const { return m_Count; }
	private:
		uint32_t m_Count;
		
		com_ptr<ID3D12Resource> indexBuffer;
		D3D12_INDEX_BUFFER_VIEW indexBufferView{};
		
	};
}
