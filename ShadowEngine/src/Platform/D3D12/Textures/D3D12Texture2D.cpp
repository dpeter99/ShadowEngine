#include "shpch.h"
#include "D3D12Texture2D.h"
#include "Platform/D3D12/DX12RendererAPI.h"

ShadowEngine::Rendering::D3D12::D3D12Texture2D::D3D12Texture2D(std::string path)
{
	auto img_temp = IMG_Load(path.c_str());
	auto img = SDL_ConvertSurfaceFormat(img_temp, SDL_PIXELFORMAT_RGBA32, 0);

	format = SDLFormatToGXGI(*img->format);
	bitsPerPixel = img->format->BitsPerPixel;

	D3D12_RESOURCE_DESC resourceDesc;
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

	this->SetupResource(resourceDesc, s2ws(path));

	ready = false;


}

/*
ShadowEngine::Rendering::D3D12::com_ptr<ID3D12Resource> ShadowEngine::Rendering::D3D12::D3D12Texture2D::GetResource()
{
	return resource;
}
*/

DXGI_FORMAT ShadowEngine::Rendering::D3D12::D3D12Texture2D::GetDXGIFormat()
{
	return format;
}

void ShadowEngine::Rendering::D3D12::D3D12Texture2D::RecordTransfer(Ref<D3D12::CommandList> commandList)
{
	D3D12_SUBRESOURCE_DATA subresource;
	subresource.RowPitch = (bitsPerPixel / 8U) * resourceDesc.Width;
	subresource.SlicePitch = (bitsPerPixel / 8U) * resourceDesc.Width;
	subresource.pData = img->pixels;
	
	commandList->CopyTextureSubresource(*this,0,1,&subresource);
}

void ShadowEngine::Rendering::D3D12::D3D12Texture2D::FinishedUploading()
{
	ready = true;
}

D3D12_CPU_DESCRIPTOR_HANDLE ShadowEngine::Rendering::D3D12::D3D12Texture2D::GetShaderResourceView(const D3D12_SHADER_RESOURCE_VIEW_DESC* srvDesc) const
{
	return D3D12_CPU_DESCRIPTOR_HANDLE();
}

D3D12_CPU_DESCRIPTOR_HANDLE ShadowEngine::Rendering::D3D12::D3D12Texture2D::GetUnorderedAccessView(const D3D12_UNORDERED_ACCESS_VIEW_DESC* uavDesc) const
{
	return D3D12_CPU_DESCRIPTOR_HANDLE();
}

void ShadowEngine::Rendering::D3D12::D3D12Texture2D::Load()
{
}

void ShadowEngine::Rendering::D3D12::D3D12Texture2D::Upload()
{
	D3D12::DX12RendererAPI::Instance->UploadResource(this);
}
