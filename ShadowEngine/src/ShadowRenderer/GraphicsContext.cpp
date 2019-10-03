#include "shpch.h"
#include "Core/Core.h"

#include "Platform/OpenGL/OpenGLContext.h"
#include "GraphicsContext.h"
#include "RendererAPI.h"

namespace ShadowEngine::Rendering {

	GraphicsContext* GraphicsContext::Create(SDL_Window* window)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:    SH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGL::OpenGLContext(window);
		}

		SH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
