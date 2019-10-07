#pragma once
#include "ShadowRenderer/GraphicsContext.h"

#include "Common.h"
#include "SDL2/SDL.h"

namespace ShadowEngine::Rendering::D3D12 {

	class D3D12Context : public GraphicsContext
	{
	public:
		D3D12Context(SDL_Window* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	public:
		SDL_Window* m_WindowHandle;
		HWND hwnd;		

		com_ptr<IDXGIFactory6> dxgiFactory{ nullptr };
		
	};

}
