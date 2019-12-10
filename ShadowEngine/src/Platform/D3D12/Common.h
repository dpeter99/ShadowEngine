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
#include <SDL.h>

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
				__debugbreak();
				//exit(-1);
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

	inline DXGI_FORMAT SDLFormatToGXGI(SDL_PixelFormat& sdl)
	{
		switch (sdl.format) {
		case SDL_PIXELFORMAT_ARGB8888:
			return DXGI_FORMAT_B8G8R8A8_UNORM;
		case SDL_PIXELFORMAT_RGB888:
			return DXGI_FORMAT_B8G8R8X8_UNORM;
		case SDL_PIXELFORMAT_YV12:
		case SDL_PIXELFORMAT_IYUV:
		case SDL_PIXELFORMAT_NV12:  /* For the Y texture */
		case SDL_PIXELFORMAT_NV21:  /* For the Y texture */
			return DXGI_FORMAT_R8_UNORM;
		case SDL_PIXELFORMAT_ABGR8888:
			return DXGI_FORMAT_R8G8B8A8_UNORM;
		default:
			return DXGI_FORMAT_UNKNOWN;

		}
	}
}