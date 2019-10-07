#include "shpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Platform/D3D12/D3D12Shader.h"

namespace ShadowEngine::Rendering {

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    SH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return new OpenGL::OpenGLShader(vertexSrc, fragmentSrc);
		}

		SH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Shader* Shader::CreateFromCompiled(const std::string& VSfilePath, const std::string& PSfilePath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    SH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::D3D12:  return new D3D12::D3D12Shader(VSfilePath, PSfilePath);
		}

		SH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
