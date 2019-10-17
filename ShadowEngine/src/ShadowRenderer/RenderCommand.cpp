#include "shpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"
#include "Renderer.h"
#include "Platform/D3D12/D3D12RendererAPI.h"

namespace ShadowEngine::Rendering {

	RendererAPI* RenderCommand::s_RendererAPI = new D3D12::D3D12RendererAPI();

}
