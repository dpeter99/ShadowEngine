#include "shpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"
#include "Renderer.h"

namespace ShadowEngine::Rendering {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGL::OpenGLRendererAPI;

}
