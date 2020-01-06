#include "shpch.h"
#include "Buffer.h"

#include "Renderer.h"

//#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Platform/D3D12/D3D12Buffers.h"

namespace ShadowEngine::Rendering {

	VertexBuffer* VertexBuffer::Create(void* vertices, uint32_t size)
	{
		switch (ShadowEngine::Rendering::Renderer::GetAPI())
		{
			case RendererAPI::API::None:    SH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			//case RendererAPI::API::OpenGL:  return new ShadowEngine::Rendering::OpenGL::OpenGLVertexBuffer(vertices, size);
			case RendererAPI::API::D3D12: return new ShadowEngine::Rendering::D3D12::D3D12VertexBuffer(vertices, size);
		}

		SH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    SH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			//case RendererAPI::API::OpenGL:  return new ShadowEngine::Rendering::OpenGL::OpenGLIndexBuffer(indices, size);
			case RendererAPI::API::D3D12: return new ShadowEngine::Rendering::D3D12::D3D12IndexBuffer(indices, size);
		}

		SH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
