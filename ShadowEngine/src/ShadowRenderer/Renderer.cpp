#include "shpch.h"
#include "Renderer.h"
#include "EntitySystem/Entities/Camera.h"
//#include "Platform/OpenGL/OpenGLShader.h"
//#include "Platform/OpenGL/OpenGLRendererAPI.h"
#include "Core/ShadowApplication.h"
#include "CommandList.h"

namespace ShadowEngine::Rendering {

	Renderer* Renderer::instance = NULL;
	
	Renderer::Renderer()
	{
	}

	void Renderer::Init()
	{
		SH_CORE_ASSERT(instance == NULL, "There is already a renderer instance");
		if (instance == NULL) {
			instance = this;
		}



		s_RendererAPI = RendererAPI::MakeRendererAPI();

		s_RendererAPI->Init(ShadowApplication::Get().GetWindow().context);

		scene = new RenderScene();
	}

	void Renderer::Update()
	{
		s_RendererAPI->StartResourceUpload();
	}

	void Renderer::Render()
	{
		RenderNodes();
	}

	
	void Renderer::BeginScene(Camera* camera)
	{
		assert(camera != nullptr);
		
		auto cb = scene->GetWorldData().get();
		(*cb)->viewProjection = camera->GetViewProjectionMatrix();
		cb->Upload();

		s_RendererAPI->StartFrame(scene->GetWorldData());
		
		s_RendererAPI->SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		s_RendererAPI->Clear();
		
		
		

	}

	void Renderer::EndScene()
	{
		s_RendererAPI->EndFrame();

		
	}

	void Renderer::RenderNodes()
	{
		for (auto& node : *instance->scene)
		{
			ConstantBuffer& cb = node->GetCB();
			s_RendererAPI->Draw(node->GetMesh(), node->GetMaterial(),cb);
		}
	}

	void Renderer::Submit(const Ref<Assets::Mesh> mesh, const Ref<Assets::Material> shader, const glm::mat4& transform)
	{
		//instance->s_RendererAPI->Draw(mesh, shader, transform);
		
	}

	Ref<RenderNode> Renderer::AddRenderNode(const Ref<Assets::Mesh> mesh, const Ref<Assets::Material> material,
		const glm::mat4& transform)
	{
		auto node = instance->scene->AddRenderNode(mesh, material);
		node->UpdateTransform(transform);
		return  node;
	}
}
