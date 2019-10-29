#include "shpch.h"
#include "Renderer.h"
#include "ShadowEntity/Entities/Camera.h"
//#include "Platform/OpenGL/OpenGLShader.h"
//#include "Platform/OpenGL/OpenGLRendererAPI.h"
#include "Core/ShadowApplication.h"
#include "CommandList.h"

namespace ShadowEngine::Rendering {

	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

	RendererAPI* Renderer::s_RendererAPI = NULL;

	void Renderer::Init()
	{
		SH_CORE_ASSERT(instance == NULL, "There is already a renderer instance");
		if (instance != NULL) {
			instance = this;
		}

		s_RendererAPI = RendererAPI::MakeRendererAPI();

		s_RendererAPI->Init(ShadowApplication::Get().GetWindow().context);
	}

	
	void Renderer::BeginScene()
	{
		s_RendererAPI->StartFrame();
		
		s_RendererAPI->SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		s_RendererAPI->Clear();
		
		//s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
		s_RendererAPI->EndFrame();

		
	}

	void Renderer::Submit(const Ref<Assets::Mesh> mesh, const Ref<Assets::Material> shader, const glm::mat4& transform)
	{
		s_RendererAPI->Draw(mesh, shader, transform);
	}

}
