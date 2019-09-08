#include "shpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace ShadowRenderer {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}