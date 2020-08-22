#pragma once
#include "ShadowRenderer/Buffer.h"
#include "Platform/D3D12/Common.h"


#include "SDL.h"
#include "SDL_image.h"
#include "Texture.h"
#include "../CommandList.h"
#include "Platform/D3D12/D3D12IUploadable.h"
#include "ShadowAsset/Assets/Textures/Texture2D.h"

namespace ShadowEngine::Rendering::D3D12 {

	
	class D3D12Texture2D : public Texture, public Assets::Texture2DImpl
	{
		//com_ptr<ID3D12Resource> resource;
		//com_ptr<ID3D12Resource> uploadResource;
		D3D12_RESOURCE_DESC resourceDesc;

		DXGI_FORMAT format;
		int bitsPerPixel;

		SDL_Surface* img;
		
		bool ready;
	public:
			
		D3D12Texture2D(std::string path);

		//com_ptr<ID3D12Resource> GetResource();
		DXGI_FORMAT GetDXGIFormat();

		// Inherited via D3D12IUploadable
		virtual void RecordTransfer(Ref<D3D12::CommandList> cmd) override;


		virtual void Upload() override;
		
		virtual void FinishedUploading() override;

	};

}
