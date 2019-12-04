#pragma once
#include "ShadowRenderer/Buffer.h"
#include "Platform/D3D12/Common.h"
#include "D3D12IUploadable.h"

#include "ShadowAsset/Assets/Texture.h"


#include "SDL.h"
#include "SDL_image.h"

namespace ShadowEngine::Rendering::D3D12 {

	
	class D3D12Texture : public D3D12IUploadable, public Assets::Texture2DImpl
	{
		com_ptr<ID3D12Resource> resource;
		com_ptr<ID3D12Resource> uploadResource;
		D3D12_RESOURCE_DESC resourceDesc;

		DXGI_FORMAT format;
		int bitsPerPixel;

		bool ready;
	public:
			
		D3D12Texture(std::string path);



		DXGI_FORMAT SDLFormatToGXGI(SDL_PixelFormat& sdl);


		com_ptr<ID3D12Resource> GetResource();
		DXGI_FORMAT GetDXGIFormat();

		// Inherited via D3D12IUploadable
		virtual void RecordTransfer(Ref<D3D12::D3D12CommandList> cmd) override;

		virtual void FinishedUploading() override;

		


		// Inherited via Texture2DImpl
		virtual void Upload() override;

	};

}