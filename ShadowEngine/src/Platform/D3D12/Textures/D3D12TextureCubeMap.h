#pragma once
#include "ShadowRenderer/Buffer.h"
#include "Platform/D3D12/Common.h"


#include "SDL.h"
#include "SDL_image.h"
#include "Texture.h"
#include "Assets/Assets/Textures/Texture.h"
#include "../CommandList.h"
#include "Platform/D3D12/D3D12IUploadable.h"
#include "Assets/Assets/Textures/TextureCubeMap.h"

namespace ShadowEngine::Rendering::D3D12 {


	class D3D12TextureCubeMap : public Texture, public Assets::TextureCubeMapImpl, public std::enable_shared_from_this<D3D12TextureCubeMap>
	{
		//std::vector<com_ptr<ID3D12Resource>> uploadResource;
		D3D12_RESOURCE_DESC resourceDesc;

		std::vector<SDL_Surface*> imgs;
		
		int bitsPerPixel;

		bool ready;
	public:

		D3D12TextureCubeMap(Assets::TextureCubeMap* asset);

		/// <summary>
		/// Inherited from Texture Impl
		/// </summary>
		void Load() override;

		// Inherited via D3D12IUploadable
		virtual void RecordTransfer(Ref<D3D12::CommandList> cmd) override;

		virtual void FinishedUploading() override;

		// Inherited via Texture2DImpl
		virtual void Upload() override;

		D3D12_CPU_DESCRIPTOR_HANDLE
		GetShaderResourceView(const D3D12_SHADER_RESOURCE_VIEW_DESC* srvDesc) const override;
		D3D12_CPU_DESCRIPTOR_HANDLE
		GetUnorderedAccessView(const D3D12_UNORDERED_ACCESS_VIEW_DESC* uavDesc) const override;
	};

}
