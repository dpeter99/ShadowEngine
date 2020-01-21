#include "shpch.h"
#include "RendererAPI.h"

//#include "Platform/OpenGL/OpenGLRendererAPI.h"
#include "Platform/D3D12/DX12RendererAPI.h"

namespace ShadowEngine::Rendering {

	RendererAPI::API RendererAPI::s_API = RendererAPI::API::D3D12;

	RendererAPI* RendererAPI::MakeRendererAPI() {

		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API::None:    SH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			//case RendererAPI::API::OpenGL:  return new OpenGL::OpenGLRendererAPI();
			case RendererAPI::API::D3D12:  return new D3D12::DX12RendererAPI();
		}

		SH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}