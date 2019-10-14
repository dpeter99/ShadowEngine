#pragma once
#include "ShadowRenderer/Buffer.h"

class D3D12VertexBuffer : public ShadowEngine::Rendering::VertexBuffer
{
public:
	D3D12VertexBuffer(void* vertices, uint32_t size);
	virtual ~D3D12VertexBuffer();

	virtual void Bind() const override;
	virtual void Unbind() const override;

	virtual const ShadowEngine::Rendering::BufferLayout& GetLayout() const override { return m_Layout; }
	virtual void SetLayout(const ShadowEngine::Rendering::BufferLayout& layout) override { m_Layout = layout; }
private:
	uint32_t m_RendererID;
	ShadowEngine::Rendering::BufferLayout m_Layout;
};

