#pragma once

#include "Core/Core.h"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <d3d12.h>
#include <d3dcompiler.h>
#include "d3dx12.h"
#include <memory>
#include <vector>

#include <string>


#include <dxgi1_5.h>

using IDXGIFactory6 = IDXGIFactory5;

#include <wrl.h>


namespace ShadowEngine::Rendering::D3D12
{
	template<typename T>
	using com_ptr = Microsoft::WRL::ComPtr<T>;

	//#define ASSERT(trueMeansOk, msgOnFail) if(!trueMeansOk) { MessageBoxA(NULL, msgOnFail, "Assertion failed!", MB_ICONSTOP | MB_OK); exit(-1); }
	#define ASSERT(trueMeansOk, msgOnFail, ...) SH_ASSERT(trueMeansOk,msgOnFail,__VA_ARGS__)
	
	inline const char* BlobAsString(com_ptr<ID3DBlob> blob) {
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

	#define OUTPUT_BUFFER_SIZE 1024
	
	inline std::wstring WFormat(const wchar_t* format, ...) {
		va_list va;
		va_start(va, format);
		std::wstring wstr;
		wstr.resize(OUTPUT_BUFFER_SIZE);
		vswprintf_s(&(wstr.at(0)), OUTPUT_BUFFER_SIZE, format, va);
		va_end(va);
		wstr.shrink_to_fit();
		return wstr;
	}
}