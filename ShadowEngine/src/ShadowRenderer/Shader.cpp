#include "shpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/D3D12/Shader/DX12Shader.h"
#include "ShadowFileFormat/SFFElement.h"

namespace ShadowEngine::Rendering {
	
	ShaderPropertySheet* Shader::GetPropertiesCopy() const
	{
		return new ShaderPropertySheet(properties);
	}

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    SH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			//case RendererAPI::API::OpenGL:  return new OpenGL::OpenGLShader(vertexSrc, fragmentSrc);
			default: SH_CORE_CRITICAL("Unknown RendererAPI: {0} !", (int)Renderer::GetAPI()); return nullptr;
		}
	}

	Shader* Shader::CreateFromCompiled(const std::string& VSfilePath, const std::string& PSfilePath)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    SH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::D3D12:  return new D3D12::DX12Shader(VSfilePath, PSfilePath);
			default: SH_CORE_CRITICAL("Unknown RendererAPI: {0} !", (int)Renderer::GetAPI()); return nullptr;
		}
	}

	void Shader::Load(SFF::SFFElement& root, Assets::FileSystem::Path path)
	{
		
		auto* shader_root = root.GetChildByName("Shader");

		SH_CORE_ASSERT(shader_root == nullptr, "Bad metadata file for {0} shader");
		
		auto vertexShader = shader_root->GetStringProperty("VertexShader");
		auto fragmentShader = shader_root->GetStringProperty("VertexShader");

		this->LoadShader(vertexShader, fragmentShader);
		
	}
}
