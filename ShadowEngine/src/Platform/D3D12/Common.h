#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <d3d12.h>
#include <d3dcompiler.h>
#include <sstream>
#include <cstdlib>
#include "d3dx12.h"
#include <vector>

#ifdef LEGACY_VERSION
#include <dxgi1_5.h>
#include <wrl.h>
using IDXGIFactory6 = IDXGIFactory5;
#else
#include <dxgi1_6.h>
#endif

namespace ShadowEngine::Rendering::D3D12
{
	template<typename T>
	using com_ptr = Microsoft::WRL::ComPtr<T>;

	#define ASSERT(trueMeansOk, msgOnFail) if(!trueMeansOk) { MessageBoxA(NULL, msgOnFail, "Assertion failed!", MB_ICONSTOP | MB_OK); exit(-1); }

	const char* BlobAsString(com_ptr<ID3DBlob> blob) {
		return reinterpret_cast<const char*>(blob->GetBufferPointer());
	}
	
	class HResultTester {
	public:
		const char* Message;
		const char* File;
		const int Line;

		HResultTester(const char* msg, const char* file, int line) : Message{ msg }, File{ file }, Line{ line } { }

		void operator<<(HRESULT hr) {
			if (FAILED(hr)) {
				std::ostringstream oss;
				oss << File << "(" << Line << "): " << Message;

				MessageBoxA(NULL, oss.str().c_str(), "Error!", MB_ICONSTOP | MB_OK);
				exit(-1);
			}
		}
	};
	
	#define DX_API(msg) HResultTester(msg, __FILE__, __LINE__) <<

}