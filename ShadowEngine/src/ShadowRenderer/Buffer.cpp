#include "shpch.h"
#include "Buffer.h"

#include "Renderer.h"

//#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Platform/D3D12/D3D12Buffers.h"
#include "Platform/D3D12/Buffers/DX12VertexBuffer.h"
#include "Platform/D3D12/Buffers/DX12IndexBuffer.h"

namespace ShadowEngine::Rendering {

	VertexBuffer* VertexBuffer::Create(std::vector<Vertex> verts)
	{
		switch (ShadowEngine::Rendering::Renderer::GetAPI())
		{
			case RendererAPI::API::None:    SH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			//case RendererAPI::API::OpenGL:  return new ShadowEngine::Rendering::OpenGL::OpenGLVertexBuffer(vertices, size);
			case RendererAPI::API::D3D12: return new ShadowEngine::Rendering::D3D12::DX12VertexBuffer(verts);
		}

		SH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(std::vector<uint32_t> indices)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    SH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			//case RendererAPI::API::OpenGL:  return new ShadowEngine::Rendering::OpenGL::OpenGLIndexBuffer(indices, size);
			case RendererAPI::API::D3D12: return new ShadowEngine::Rendering::D3D12::DX12IndexBuffer(indices);
		}

		SH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
