#pragma once
#include "ShadowRenderer/RendererAPI.h"

namespace ShadowEngine::Rendering::D3D12 {

	class D3D12RendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}
