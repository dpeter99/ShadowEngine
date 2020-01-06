#include "shpch.h"
#include "D3D12Context.h"
#include <SDL_syswm.h>

#include "ShadowWindow.h"

namespace ShadowEngine::Rendering::D3D12 {

	D3D12Context::D3D12Context(ShadowWindow* windowHandle)
		: m_WindowHandle(windowHandle->winPtr)
	{
		window = windowHandle;
		
		//Check the window we got
		SH_CORE_ASSERT(windowHandle, "Window handle is null!")

		SDL_SysWMinfo wmInfo;
		SDL_VERSION(&wmInfo.version);
		SDL_GetWindowWMInfo(m_WindowHandle, &wmInfo);
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
