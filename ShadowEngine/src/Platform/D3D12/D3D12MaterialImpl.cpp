#include "shpch.h"
#include "D3D12MaterialImpl.h"
#include "Textures/D3D12Texture2D.h"
#include "ShadowAsset/Assets/Textures/TextureCubeMap.h"
#include "Textures/D3D12TextureCubeMap.h"

namespace ShadowEngine::Rendering::D3D12 {

	D3D12MaterialImpl::D3D12MaterialImpl(Ref<ShaderPropertySheet> propertySheet) : propertySheet(propertySheet)
	{
		//Constant Buffer object

		this->shaderData = std::make_shared<Rendering::ConstantBuffer_ShaderPropertySheet>(propertySheet);
		D3D12ConstantBuffer* dx12_buffer = ((D3D12ConstantBuffer*)shaderData->GetImpl().get());
		shaderData->Upload();


		//Descriptor Table
		table = D3D12RendererAPI::Instance->descriptorHeap_SRV_CBV->Allocate(1 + propertySheet->GetTextureCount());

		//Constant Buffer descriptor

		D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
		cbvDesc.BufferLocation = dx12_buffer->GetGPUVirtualAddress();
		cbvDesc.SizeInBytes = dx12_buffer->GetSize(); // CB size is required to be 256-byte aligned.
		D3D12RendererAPI::device->CreateConstantBufferView(&cbvDesc, table.CPU_TableStart);

		//Textures Descriptor

		for (size_t i = 0; i < propertySheet->GetTextureCount(); i++)
		{
			auto* prop = propertySheet->GetTexture<Assets::Texture>(i);


			CreateTextureResourceView(i, prop);
		}

	}

	void D3D12MaterialImpl::BindMaterialData(Ref<D3D12CommandList> commandList)
	{
		commandList->BindDescriptorTableBuffer(table.GPU_TableStart, 2);
	}

	void D3D12MaterialImpl::Upload()
	{
		shaderData->Upload();
	}

	void D3D12MaterialImpl::CreateTextureResourceView(size_t i, ShaderRefProperty<Assets::Texture>* prop)
	{
		if (!prop->IsEmpty()) {

			int type = prop->GetPropertyDataTyped().GetTypeId();

			D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};


			if (type == Assets::Texture2D::TypeId())
			{
				auto a = std::dynamic_pointer_cast<D3D12::D3D12Texture2D>(prop->GetPropertyDataTyped().getImpl());

				srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
				srvDesc.Format = a->GetDXGIFormat();
				srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
				prop->GetPropertyData();
				srvDesc.Texture2D.MipLevels = 1;
				D3D12RendererAPI::device->CreateShaderResourceView(a->GetResource().Get(), &srvDesc,
					table[i+1].CPU_TableStart);
			}
			if (type == Assets::TextureCubeMap::TypeId())
			{
				auto a = std::dynamic_pointer_cast<D3D12::D3D12TextureCubeMap>(prop->GetPropertyDataTyped().getImpl());

				srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;
				srvDesc.Format = a->GetDXGIFormat();
				srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
				prop->GetPropertyData();
				srvDesc.Texture2D.MipLevels = 1;
				D3D12RendererAPI::device->CreateShaderResourceView(a->GetResource().Get(), &srvDesc,
					table[i + 1].CPU_TableStart);
			}
		}
		
	}

	void D3D12MaterialImpl::UploadTextures()
	{
		//TODO: This will not work once we have more than one command list and back buffering of commands

		for (size_t i = 0; i < propertySheet->GetTextureCount(); i++)
		{
			auto* prop = propertySheet->GetTexture<Assets::Texture>(i);

			CreateTextureResourceView(i, prop);
		}
	}
}
