#include "shpch.h"
#include "Core/Core.h"

#include "ShadowRenderer/GraphicsContext.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace ShadowRenderer {

	GraphicsContext* GraphicsContext::Create(SDL_Window* window)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:    SH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLContext(window);
		}

		SH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}