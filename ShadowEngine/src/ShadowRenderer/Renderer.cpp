#include "shpch.h"
#include "Renderer.h"
#include "EntitySystem/Entities/Camera.h"
#include "Core/ShadowApplication.h"

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

		frame_index = 0;

		s_RendererAPI = RendererAPI::MakeRendererAPI();

		s_RendererAPI->Init(ShadowApplication::Get().GetWindow().context);

		scene = new RenderScene();
	}

	void Renderer::Update()
	{
		s_RendererAPI->StartResourceUpload();
	}

	


	//TODO: Assign camera somewhere else
	void Renderer::BeginScene(Camera* camera)
	{
		//assert(camera != nullptr);

		
		frame_index++;
		
		scene->SetCamera(camera);

		//scene->PrepareWorldData();

		s_RendererAPI->SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		
		s_RendererAPI->StartFrame(scene->GetWorldData(), frame_index);
		
		//s_RendererAPI->Clear();
	}

	void Renderer::Render()
	{
		RenderNodes();
	}
	
	void Renderer::EndScene()
	{
		s_RendererAPI->EndFrame();

		
	}

	void Renderer::RenderNodes()
	{
		for (auto& node : *instance->scene)
		{
			ConstantBuffer& model_data = node->GetCB();
			s_RendererAPI->Draw(node->GetMesh(), node->GetMaterial(),model_data);
		}
	}

	void Renderer::Submit (const Ref<Assets::Mesh> mesh, const Ref<Assets::Material> shader, const glm::mat4& transform)
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

	Ref<LightNode> Renderer::AddLightNode()
	{
		auto node = instance->scene->AddLightNode();
		return  node;
	}
}
