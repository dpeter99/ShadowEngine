#include "shpch.h"
#include "D3D12Texture2D.h"
#include "Platform/D3D12/D3D12RendererAPI.h"

ShadowEngine::Rendering::D3D12::D3D12Texture2D::D3D12Texture2D(std::string path)
{
	auto img_temp = IMG_Load(path.c_str());
	auto img = SDL_ConvertSurfaceFormat(img_temp, SDL_PIXELFORMAT_RGBA32, 0);

	format = SDLFormatToGXGI(*img->format);
	bitsPerPixel = img->format->BitsPerPixel;

	//D3D12_RESOURCE_DESC rdsc;
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

	//com_ptr<ID3D12Resource> resource;
	//com_ptr<ID3D12Resource> uploadResource;

	DX_API("failed to create committed resource for texture file")
		D3D12RendererAPI::device->CreateCommittedResource(
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
			D3D12_HEAP_FLAG_NONE,
			&resourceDesc,
			D3D12_RESOURCE_STATE_COPY_DEST,
			nullptr,
			IID_PPV_ARGS(resource.GetAddressOf()));

	resource->SetName(s2ws("Texture2D Commited resource").c_str());
	
	UINT64 copyableSize;
	D3D12RendererAPI::device->GetCopyableFootprints(&resourceDesc, 0, 1, 0, nullptr, nullptr, nullptr, &copyableSize);

	DX_API("failed to create committed resource for texture file (upload buffer)")
		D3D12RendererAPI::device->CreateCommittedResource(
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
			D3D12_HEAP_FLAG_NONE,
			&CD3DX12_RESOURCE_DESC::Buffer(copyableSize),
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(uploadResource.GetAddressOf()));

	uploadResource->SetName(s2ws("Texture2D upload resource resource").c_str());

	
	CD3DX12_RANGE readRange{ 0,0 };
	void* mappedPtr;
	
	DX_API("Failed to map upload resource")
		uploadResource->Map(0, &readRange, &mappedPtr);

	memcpy(mappedPtr, img->pixels, img->pitch * img->h);

	uploadResource->Unmap(0, nullptr);

	ready = false;


}

ShadowEngine::Rendering::D3D12::com_ptr<ID3D12Resource> ShadowEngine::Rendering::D3D12::D3D12Texture2D::GetResource()
{
	return resource;
}

DXGI_FORMAT ShadowEngine::Rendering::D3D12::D3D12Texture2D::GetDXGIFormat()
{
	return format;
}

void ShadowEngine::Rendering::D3D12::D3D12Texture2D::RecordTransfer(Ref<D3D12::D3D12CommandList> commandList)
{
	CD3DX12_TEXTURE_COPY_LOCATION dst{ resource.Get(), 0 };
	D3D12_PLACED_SUBRESOURCE_FOOTPRINT psf;
	psf.Offset = 0;
	psf.Footprint.Depth = 1;
	psf.Footprint.Height = resourceDesc.Height;
	psf.Footprint.Width = resourceDesc.Width;
	psf.Footprint.RowPitch = (bitsPerPixel / 8U) * resourceDesc.Width;
	psf.Footprint.Format = resourceDesc.Format;
	CD3DX12_TEXTURE_COPY_LOCATION src{ uploadResource.Get(), psf };
	commandList->CopyTextureRegion( &src, &dst);
	commandList->ResourceBarrier(&CD3DX12_RESOURCE_BARRIER::Transition(resource.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_COMMON));
}

void ShadowEngine::Rendering::D3D12::D3D12Texture2D::FinishedUploading()
{
	ready = true;
}

void ShadowEngine::Rendering::D3D12::D3D12Texture2D::Upload()
{
	D3D12::D3D12RendererAPI::Instance->UploadResource(this->shared_from_this());
}
