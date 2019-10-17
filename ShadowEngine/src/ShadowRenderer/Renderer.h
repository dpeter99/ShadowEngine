#pragma once
#include "Core/Core.h"
#include "ShadowModules/ShadowModule.h"

//#include "RenderCommand.h"
#include "RendererAPI.h"

#include "OrthographicCamera.h"
#include "Shader.h"
#include "CommandQueue.h"
#include "SwapChain.h"


class Camera;

namespace ShadowEngine::Rendering {

	class Renderer : public ShadowEngine::ShadowModule
	{
		SHObject_Base(Renderer)

	public:
		//Singleton Instance
		Renderer* instance;

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

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

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
