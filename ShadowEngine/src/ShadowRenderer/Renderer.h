#pragma once
#include "Core/Core.h"
#include "ShadowModules/ShadowModule.h"

//#include "RenderCommand.h"
#include "RendererAPI.h"

#include "OrthographicCamera.h"
#include "Shader.h"
#include "ShadowAsset/Assets/Mesh.h"

#include "ShadowRenderer/DataStructs.h"
#include "RenderScene.h"


class Camera;

namespace ShadowEngine::Rendering {
	
	class Renderer : public ShadowEngine::ShadowModule
	{
		SHObject_Base(Renderer)
		
	private:
		RendererAPI* s_RendererAPI;

		RenderScene* scene;
		
	public:
		Renderer();

		//Singleton Instance
		static Renderer* instance;

		void Init() override;
		void Update() override {};
		void Render() override;
		void LateRender() override {};

		std::string GetName() override { return "Renderer"; }



		/**
		 * \brief Starts the Rendering scene
		 * Sets up the render API
		 * Sets up the render graph for the new frame
		 */
		void BeginScene(Camera* camera);
		
		/**
		 * \brief Finishes the draw recording
		 */
		void EndScene();

		void RenderNodes();
		
		static void Submit(const Ref<Assets::Mesh> mesh, const Ref<Assets::Material> shader, const glm::mat4& transform = glm::mat4(1.0f));

		static Ref<RenderNode> AddRenderNode(const Ref<Assets::Mesh> mesh, const Ref<Assets::Material> material, const glm::mat4& transform = glm::mat4(1.0f));
		
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	};


}
