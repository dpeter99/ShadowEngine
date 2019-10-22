#pragma once
#include "ShadowRenderer/Buffer.h"


namespace ShadowEngine::Rendering::OpenGL {

	class OpenGLVertexBuffer : public ShadowEngine::Rendering::VertexBuffer
	{
	public:
		OpenGLVertexBuffer(void* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		//TODO: fix
		//virtual void Bind() const override;
		//virtual void Unbind() const override;

		virtual const BufferLayout& GetLayout() const override { return m_Layout; }
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		//TODO: fix
		//virtual void Bind() const;
		//virtual void Unbind() const;

		virtual uint32_t GetCount() const { return m_Count; }
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};

}
