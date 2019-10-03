#pragma once

#include <glm/glm.hpp>

#include "VertexArray.h"
#include "GraphicsContext.h"

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
		virtual void Init(GraphicsContext& ctx) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

		inline static API GetAPI() { return s_API; }

		static RendererAPI* RendererAPI::MakeRendererAPI();
	private:
		static API s_API;
	};

}