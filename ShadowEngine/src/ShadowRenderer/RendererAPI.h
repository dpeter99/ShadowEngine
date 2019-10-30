#pragma once

#include <glm/glm.hpp>

#include "GraphicsContext.h"
#include "Shader.h"
#include "ShadowAsset/Assets/Mesh.h"
#include "ShadowAsset/Assets/Material.h"

namespace ShadowEngine::Rendering {
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0,
			OpenGL = 1,
			D3D12 = 2
		};
	public:
		virtual void Init(ShadowEngine::Ref<GraphicsContext> ctx) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void Draw(const Ref<Assets::Mesh> mesh, const Ref<Assets::Material> shader, const glm::mat4& transform = glm::mat4(1.0f)) =0;
		virtual void Draw(const std::shared_ptr<Assets::Mesh>& mesh, const std::shared_ptr<Assets::Material>& shader, const ConstantBuffer& materialData) =0;

		/**
		 * \brief Starts recording the draw commands
		 */
		virtual  void StartFrame(Ref<ConstantBuffer> worldCB) = 0;
		
		/**
		 * \brief Finalizes the render command recording
		 */
		virtual void EndFrame() =0;
		

		inline static API GetAPI() { return s_API; }

		static RendererAPI* RendererAPI::MakeRendererAPI();
	private:
		static API s_API;
	};

}
