#include "shpch.h"
#include "D3D12Context.h"

namespace ShadowEngine::Rendering::D3D12 {

	D3D12Context::D3D12Context(SDL_Window* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		SH_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void GetAdapters(IDXGIFactory6* dxgiFactory, std::vector<com_ptr<IDXGIAdapter1>>& adapters) {
		HRESULT adapterQueryResult;
		unsigned int adapterId = 0;
		OutputDebugStringW(L"Detected Video Adapters:\n");
		do {
			com_ptr<IDXGIAdapter1> tempAdapter{ nullptr };
			adapterQueryResult = dxgiFactory->EnumAdapters1(adapterId, tempAdapter.GetAddressOf());

			if (adapterQueryResult != S_OK && adapterQueryResult != DXGI_ERROR_NOT_FOUND) {
				ASSERT(false, "Failed to query DXGI adapter");
			}

			if (tempAdapter != nullptr) {
				DXGI_ADAPTER_DESC desc;
				tempAdapter->GetDesc(&desc);

				OutputDebugStringW(L"\t");
				OutputDebugStringW(desc.Description);
				OutputDebugStringW(L"\n");

				adapters.push_back(std::move(tempAdapter));
			}

			adapterId++;
		} while (adapterQueryResult != DXGI_ERROR_NOT_FOUND);
	}
	
	void D3D12Context::Init()
	{
		DX_API("Failed to create DXGI factory")
			CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory));

		std::vector<com_ptr<IDXGIAdapter1>> adapters;
		GetAdapters(dxgiFactory.Get(), adapters);

		// select your adapter here, NULL = system default
		IUnknown* selectedAdapter = (adapters.size() > 0) ? adapters[0].Get() : NULL;

		DX_API("Failed to create D3D Device")
			D3D12CreateDevice(selectedAdapter, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(device.GetAddressOf()));

	}

	
	
}