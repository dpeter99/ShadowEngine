#include "shpch.h"
#include "Core/Core.h"

#include "Platform/OpenGL/OpenGLContext.h"
#include "Platform/D3D12/D3D12Context.h"

#include "GraphicsContext.h"
#include "RendererAPI.h"

namespace ShadowEngine::Rendering {

	Ref<GraphicsContext> GraphicsContext::Create(SDL_Window* window)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API::None:    SH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return std::make_shared<OpenGL::OpenGLContext>(window);
			case RendererAPI::API::D3D12: return std::make_shared <D3D12::D3D12Context>(window);
		}

		SH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
