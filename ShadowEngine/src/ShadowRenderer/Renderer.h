#pragma once
#include "Core/Core.h"
#include "ShadowModules/ShadowModule.h"

//#include "RenderCommand.h"
#include "RendererAPI.h"

#include "OrthographicCamera.h"
#include "Shader.h"


class Camera;

namespace ShadowEngine::Rendering {

	class Renderer : public ShadowEngine::ShadowModule
	{
		SHObject_Base(Renderer)
		
	public:
		Renderer* instance;

		
		void Init() override;
		void Update() override {};
		void Render() override {};
		void LateRender() override {};
		
		std::string GetName() override { return "Renderer"; }

		static void BeginScene(Camera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

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
