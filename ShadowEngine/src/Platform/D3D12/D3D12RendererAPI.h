#pragma once
#include "ShadowRenderer/RendererAPI.h"

#include "Common.h"
#include "Platform/D3D12/D3D12Context.h"


namespace ShadowEngine::Rendering::D3D12 {

	class D3D12RendererAPI : public RendererAPI
	{
	public:
		static com_ptr<ID3D12Device> device;
		static ShadowEngine::Ref<D3D12::D3D12Context> ctx;
		
		virtual void Init(ShadowEngine::Ref<GraphicsContext> ctx) override;

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}
