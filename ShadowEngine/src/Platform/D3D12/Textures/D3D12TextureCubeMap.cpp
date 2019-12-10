#include "shpch.h"

#include "D3D12TextureCubeMap.h"
#include "Platform/D3D12/D3D12RendererAPI.h"

namespace ShadowEngine::Rendering::D3D12 {

	D3D12TextureCubeMap::D3D12TextureCubeMap(std::string path)
	{
		auto img_temp = IMG_Load(path.c_str());


		//D3D12_RESOURCE_DESC for the GPU resource;
		ZeroMemory(&resourceDesc, sizeof(D3D12_RESOURCE_DESC));
		resourceDesc.DepthOrArraySize = 6;
		resourceDesc.Height = (unsigned int)img_temp->h;
		resourceDesc.Width = (unsigned int)img_temp->w;
		resourceDesc.Format = SDLFormatToGXGI(*img_temp->format);
		resourceDesc.MipLevels = 1;
		resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
		resourceDesc.Alignment = 0;
		resourceDesc.SampleDesc.Count = 1;
		resourceDesc.SampleDesc.Quality = 0;
		resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
		resourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

		SDL_FreeSurface(img_temp);

		UINT64 copyableSize;
		D3D12RendererAPI::device->GetCopyableFootprints(&resourceDesc, 0, 6, 0, nullptr, nullptr, nullptr, &copyableSize);

		//Load in the images
		for (size_t i = 0; i < 6; i++)
		{
			auto img_temp = IMG_Load(path.c_str());
			auto img = SDL_ConvertSurfaceFormat(img_temp, SDL_PIXELFORMAT_RGBA32, 0);

			format = SDLFormatToGXGI(*img->format);
			bitsPerPixel = img->format->BitsPerPixel;

			//CPU side descriptor;
			ZeroMemory(&resourceDesc, sizeof(D3D12_RESOURCE_DESC));
			resourceDesc.DepthOrArraySize = 1;
			resourceDesc.Height = (unsigned int)img->h;
			resourceDesc.Width = (unsigned int)img->w;
			resourceDesc.Format = SDLFormatToGXGI(*img->format);
			resourceDesc.MipLevels = 1;
			resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
			resourceDesc.Alignment = 0;
			resourceDesc.SampleDesc.Count = 1;
			resourceDesc.SampleDesc.Quality = 0;
			resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
			resourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

			com_ptr<ID3D12Resource> cpuRes;

			DX_API("failed to create committed resource for texture file (upload buffer)")
				D3D12RendererAPI::device->CreateCommittedResource(
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
			D3D12RendererAPI::device->CreateCommittedResource(
				&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
				D3D12_HEAP_FLAG_NONE,
				&resourceDesc,
				D3D12_RESOURCE_STATE_COPY_DEST,
				nullptr,
				IID_PPV_ARGS(resource.GetAddressOf()));

		resource->SetName(s2ws("Texture2D Committed resource").c_str());


		ready = false;
	}

	void D3D12TextureCubeMap::RecordTransfer(Ref<D3D12CommandList> commandList)
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
		D3D12RendererAPI::Instance->UploadResource(this->shared_from_this());
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