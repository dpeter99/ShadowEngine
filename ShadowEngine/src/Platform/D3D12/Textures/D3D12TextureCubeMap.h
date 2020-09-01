#pragma once
#include "ShadowRenderer/Buffer.h"
#include "Platform/D3D12/Common.h"


#include "SDL.h"
#include "SDL_image.h"
#include "Assets/Assets/Textures/Texture.h"
#include "../CommandList.h"
#include "Platform/D3D12/D3D12IUploadable.h"
#include "Assets/Assets/Textures/TextureCubeMap.h"

namespace ShadowEngine::Rendering::D3D12 {


	class D3D12TextureCubeMap : public D3D12IUploadable, public Assets::TextureCubeMapImpl, public std::enable_shared_from_this<D3D12TextureCubeMap>
	{
		com_ptr<ID3D12Resource> resource;
		std::vector<com_ptr<ID3D12Resource>> uploadResource;
		D3D12_RESOURCE_DESC resourceDesc;

		DXGI_FORMAT format;
		int bitsPerPixel;

		bool ready;
	public:

		D3D12TextureCubeMap(std::string path);


		com_ptr<ID3D12Resource> GetResource();
		DXGI_FORMAT GetDXGIFormat();

		// Inherited via D3D12IUploadable
		virtual void RecordTransfer(Ref<D3D12::CommandList> cmd) override;

		virtual void FinishedUploading() override;

		// Inherited via Texture2DImpl
		virtual void Upload() override;

	};

}
