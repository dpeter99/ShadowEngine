#include "shpch.h"
#include "Renderer.h"
#include "ShadowEntity/Entities/Camera.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"
#include "Core/ShadowApplication.h"

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

		commandQueue = CommandQueue::Create();

		swapChain = SwapChain::Create(commandQueue);
	}

	void Renderer::BeginScene(Camera& camera)
	{

		s_RendererAPI->SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		s_RendererAPI->Clear();
		
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();

		//TODO: this should not need a cast
		std::dynamic_pointer_cast<OpenGL::OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGL::OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

		vertexArray->Bind();
		s_RendererAPI->DrawIndexed(vertexArray);
	}

}
