#include "shpch.h"

#include "D3D12TextureCubeMap.h"
#include "Platform/D3D12/DX12RendererAPI.h"

namespace ShadowEngine::Rendering::D3D12 {

	std::string GetCubemapFileName(std::string path, int i) {
		auto poss = path.find_last_of(".");
		if (poss != std::string::npos) {
			std::string postfix;
			switch (i) {
			case 0:
				postfix = "_ft";
				break;
			case 1:
				postfix = "_bk";
				break;
			case 2:
				postfix = "_up";
				break;
			case 3:
				postfix = "_dn";
				break;
			case 4:
				postfix = "_rt";
				break;
			case 5:
				postfix = "_lf";
				break;
			}

			path = path.insert(poss, postfix);
		}

		return path;
	}

	D3D12TextureCubeMap::D3D12TextureCubeMap(std::string path)
	{
		std::string temp = GetCubemapFileName(path,0);
		auto img_temp = IMG_Load(temp.c_str());
		auto img_temp_converted = SDL_ConvertSurfaceFormat(img_temp, SDL_PIXELFORMAT_RGBA32, 0);

		//D3D12_RESOURCE_DESC for the GPU resource;
		ZeroMemory(&resourceDesc, sizeof(D3D12_RESOURCE_DESC));
		resourceDesc.DepthOrArraySize = 6;
		resourceDesc.Height = (unsigned int)img_temp_converted->h;
		resourceDesc.Width = (unsigned int)img_temp_converted->w;
		resourceDesc.Format = SDLFormatToGXGI(*img_temp_converted->format);
		resourceDesc.MipLevels = 1;
		resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
		resourceDesc.Alignment = 0;
		resourceDesc.SampleDesc.Count = 1;
		resourceDesc.SampleDesc.Quality = 0;
		resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
		resourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

		SDL_FreeSurface(img_temp);
		SDL_FreeSurface(img_temp_converted);

		UINT64 copyableSize;
		DX12RendererAPI::device->GetCopyableFootprints(&resourceDesc, 0, 6, 0, nullptr, nullptr, nullptr, &copyableSize);

		//Load in the images
		for (size_t i = 0; i < 6; i++)
		{
			

			auto img_temp = IMG_Load(GetCubemapFileName(path,i).c_str());
			auto img = SDL_ConvertSurfaceFormat(img_temp, SDL_PIXELFORMAT_RGBA32, 0);

			format = SDLFormatToGXGI(*img->format);
			bitsPerPixel = img->format->BitsPerPixel;

			com_ptr<ID3D12Resource> cpuRes;

			DX_API("failed to create committed resource for texture file (upload buffer)")
				DX12RendererAPI::device->CreateCommittedResource(
					&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
					D3D12_HEAP_FLAG_NONE,
					&CD3DX12_RESOURCE_DESC::Buffer(copyableSize),
					D3D12_RESOURCE_STATE_GENERIC_READ,
					nullptr,
					IID_PPV_ARGS(cpuRes.GetAddressOf()));

			cpuRes->SetName(s2ws("Texture2D upload resource resource").c_str());


			CD3DX12_RANGE readRange{ 0,0 };
			void* mappedPtr;

			DX_API("Failed to map upload resource")
				cpuRes->Map(0, &readRange, &mappedPtr);

			memcpy(mappedPtr, img->pixels, img->pitch * img->h);

			cpuRes->Unmap(0, nullptr);

			uploadResource.push_back(cpuRes);
		}


		DX_API("failed to create committed resource for texture file")
			DX12RendererAPI::device->CreateCommittedResource(
				&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
				D3D12_HEAP_FLAG_NONE,
				&resourceDesc,
				D3D12_RESOURCE_STATE_COPY_DEST,
				nullptr,
				IID_PPV_ARGS(resource.GetAddressOf()));

		resource->SetName(s2ws("Texture2D Committed resource").c_str());


		ready = false;
	}

	void D3D12TextureCubeMap::RecordTransfer(Ref<CommandList> commandList)
	{
		for (UINT i = 0; i < 6; i++)
		{
			CD3DX12_TEXTURE_COPY_LOCATION dst{ resource.Get(), i };

			D3D12_PLACED_SUBRESOURCE_FOOTPRINT psf;
			psf.Offset = 0;
			psf.Footprint.Depth = 1;
			psf.Footprint.Height = resourceDesc.Height;
			psf.Footprint.Width = resourceDesc.Width;
			psf.Footprint.RowPitch = (bitsPerPixel / 8U) * resourceDesc.Width;
			psf.Footprint.Format = resourceDesc.Format;
			CD3DX12_TEXTURE_COPY_LOCATION src{ uploadResource[i].Get(), psf };
			commandList->CopyTextureRegion(&src, &dst);
		}

		commandList->ResourceBarrier(&CD3DX12_RESOURCE_BARRIER::Transition(resource.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_COMMON));
	}

	void D3D12TextureCubeMap::FinishedUploading()
	{
		ready = true;
	}

	void D3D12TextureCubeMap::Upload()
	{
		DX12RendererAPI::Instance->UploadResource(this->shared_from_this());
	}

	com_ptr<ID3D12Resource> D3D12TextureCubeMap::GetResource()
	{
		return resource;
	}

	DXGI_FORMAT D3D12TextureCubeMap::GetDXGIFormat()
	{
		return format;
	}

}