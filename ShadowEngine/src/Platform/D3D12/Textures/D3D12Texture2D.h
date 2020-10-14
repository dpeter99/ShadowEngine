#pragma once
#include "ShadowRenderer/Buffer.h"
#include "Platform/D3D12/Common.h"


#include "SDL.h"
#include "SDL_image.h"
#include "Texture.h"
#include "../CommandList.h"
#include "Platform/D3D12/D3D12IUploadable.h"
#include "Assets/Assets/Textures/Texture2D.h"

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
			
		D3D12Texture2D(Assets::Texture2D* asset);

		//com_ptr<ID3D12Resource> GetResource();
		//DXGI_FORMAT GetDXGIFormat();

		// Inherited via D3D12IUploadable
		virtual void RecordTransfer(Ref<D3D12::CommandList> cmd) override;


		virtual void Upload() override;
		
		virtual void FinishedUploading() override;

		D3D12_CPU_DESCRIPTOR_HANDLE
		GetShaderResourceView(const D3D12_SHADER_RESOURCE_VIEW_DESC* srvDesc) const override;
		D3D12_CPU_DESCRIPTOR_HANDLE
		GetUnorderedAccessView(const D3D12_UNORDERED_ACCESS_VIEW_DESC* uavDesc) const override;
		void Load() override;
	};

}
