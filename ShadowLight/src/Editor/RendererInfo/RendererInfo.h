#pragma once

#include "../EditorWindow.h"

//#include "ShadowRenderer/Renderer.h"
//#include "Platform/D3D12/DX12RendererAPI.h"

namespace ShadowEngine::Rendering {
	class Renderer;

	namespace D3D12
	{
		class DX12RendererAPI;
	}
}

namespace ShadowLight::Editor {

	class RendererInfo : public EditorWindow
	{
		bool active = true;

		ShadowEngine::Rendering::Renderer* renderer = nullptr;

		ShadowEngine::Rendering::D3D12::DX12RendererAPI* d3d12Renderer = nullptr;

		void D3D12Inspector();
	public:
		void Draw() override;
	};

}
