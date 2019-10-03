#include "shpch.h"
#include "D3D12RendererAPI.h"
#include "D3D12Context.h"

namespace ShadowEngine::Rendering::D3D12 {

	com_ptr<ID3D12Device> D3D12RendererAPI::device{ nullptr };
	
	/**
	 * \brief Loads the GPU adapters
	 * \param dxgiFactory DXGI factory instance
	 * \param adapters Returns the Vector of adapters
	 */
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
	
	void D3D12RendererAPI::Init(GraphicsContext& _ctx)
	{
		D3D12::D3D12Context& ctx = dynamic_cast<D3D12::D3D12Context&>(_ctx);
		
		//Load in the GPU adapters
		std::vector<com_ptr<IDXGIAdapter1>> adapters;
		GetAdapters(ctx.dxgiFactory.Get(), adapters);

		// select your adapter here, NULL = system default
		// Using the first adapter for now
		IUnknown* selectedAdapter = (adapters.size() > 0) ? adapters[0].Get() : NULL;

		//Create the D3D device
		DX_API("Failed to create D3D Device")
			D3D12CreateDevice(selectedAdapter, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(device.GetAddressOf()));
	}

	void D3D12RendererAPI::SetClearColor(const glm::vec4& color)
	{

	}

	void D3D12RendererAPI::Clear()
	{
	}

	void D3D12RendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
	}
}
