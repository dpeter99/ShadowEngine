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
		RenderScene scene;
		
	public:
		//Singleton Instance
		static Renderer* instance;

		void Init() override;
		void Update() override {};
		void Render() override {};
		void LateRender() override {};

		std::string GetName() override { return "Renderer"; }



		/**
		 * \brief Starts the Rendering scene
		 * Sets up the render API
		 * Sets up the render graph for the new frame
		 */
		static void BeginScene();
		
		/**
		 * \brief Finishes the draw recording
		 */
		static void EndScene();

		static void RenderNodes();
		
		static void Submit(const Ref<Assets::Mesh> mesh, const Ref<Assets::Material> shader, const glm::mat4& transform = glm::mat4(1.0f));

		static Ref<RenderNode> AddRenderNode(const Ref<Assets::Mesh> mesh, const Ref<Assets::Material> material, const glm::mat4& transform = glm::mat4(1.0f));
		
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }


	private:

		static RendererAPI* s_RendererAPI;

		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* s_SceneData;
	};


}
