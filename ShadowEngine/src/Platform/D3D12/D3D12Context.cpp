#include "shpch.h"
#include "D3D12Context.h"
#include <SDL2/SDL_syswm.h>

namespace ShadowEngine::Rendering::D3D12 {

	D3D12Context::D3D12Context(SDL_Window* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		//Check the window we got
		SH_CORE_ASSERT(windowHandle, "Window handle is null!")

		SDL_SysWMinfo wmInfo;
		SDL_VERSION(&wmInfo.version);
		SDL_GetWindowWMInfo(windowHandle, &wmInfo);
		hwnd = (HWND)wmInfo.info.win.window;
	}
	
	void D3D12Context::Init()
	{
		//DXGI for rendered frame handling		
		DX_API("Failed to create DXGI factory")
			CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory));
	}

	void D3D12Context::SwapBuffers()
	{
	}
}
