#pragma once
#include "ShadowRenderer/GraphicsContext.h"

#include "Common.h"
#include <SDL.h>
#include "ShadowWindow.h"

namespace ShadowEngine::Rendering::D3D12 {

	class D3D12Context : public GraphicsContext
	{
	public:
		D3D12Context(ShadowWindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	public:
		SDL_Window* m_WindowHandle;
		HWND hwnd;
		ShadowWindow* window;

		com_ptr<IDXGIFactory6> dxgiFactory{ nullptr };
		
	};

}
