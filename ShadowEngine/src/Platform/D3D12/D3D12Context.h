#pragma once
#include "Common.h"

#include "SDL2/SDL.h"
#include "ShadowRenderer/GraphicsContext.h"


namespace ShadowEngine::Rendering::D3D12 {

	class D3D12Context : public GraphicsContext
	{
	public:
		D3D12Context(SDL_Window* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		SDL_Window* m_WindowHandle;

		com_ptr<IDXGIFactory6> dxgiFactory{ nullptr };
		com_ptr<ID3D12Device> device{ nullptr };
	};

}
