#include "shpch.h"
#include "D3D12MaterialImpl.h"
#include "Textures/D3D12Texture2D.h"
#include "Assets/Assets/Textures/TextureCubeMap.h"
#include "Textures/D3D12TextureCubeMap.h"
#include "Textures/Texture.h"

namespace ShadowEngine::Rendering::D3D12 {

	D3D12MaterialImpl::D3D12MaterialImpl(Ref<ShaderPropertySheet> propertySheet) : propertySheet(propertySheet)
	{
		//Constant Buffer object

		this->shaderData = std::make_shared<Rendering::ConstantBuffer_ShaderPropertySheet>(propertySheet);
		dx12_buffer = ((DX12ConstantBuffer*)shaderData->GetImpl().get());
		shaderData->Upload();


		//Descriptor Table
		//table = DX12RendererAPI::Get().AllocateDescriptors(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,1 + propertySheet->GetTextureCount());

		//Constant Buffer descriptor

		//D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
		//cbvDesc.BufferLocation = dx12_buffer->GetGPUVirtualAddress();
		//cbvDesc.SizeInBytes = dx12_buffer->GetSize(); // CB size is required to be 256-byte aligned.
		//DX12RendererAPI::device->CreateConstantBufferView(&cbvDesc, table.GetDescriptorHandle(0));

		//Textures Descriptor

		//for (size_t i = 0; i < propertySheet->GetTextureCount(); i++)
		//{
		//	auto* prop = propertySheet->GetTexture<Assets::Texture>(i);
		//
		//
		//	CreateTextureResourceView(i, prop);
		//}

	}

	void D3D12MaterialImpl::BindMaterialData(Ref<CommandList> commandList)
	{
		//commandList->BindDescriptorTableBuffer(table.GPU_TableStart, 2);

		//Bind the CB in the table
		commandList->SetShaderConstandBufferView(rootSigIndex, 0, *dx12_buffer);
		
		//Bind the textures in the table
		for (size_t i = 0; i < propertySheet->GetTextureCount(); i++)
		{
			auto* prop = propertySheet->GetTexture<Assets::Texture>(i);
			//TODO: FIX this
			//auto texture = prop->GetPropertyDataTyped();

			//auto a = std::dynamic_pointer_cast<D3D12::Texture>(texture.getImpl());

			///CreateTextureResourceView(i, prop);
			//commandList->SetShaderResourceView(this->rootSigIndex, i+1, *a);
		}
		
		
		
		//propertySheet->GetTexture<Assets::Texture>(0)->GetPropertyDataTyped<Texture>()
		
		//commandList->SetShaderResourceView(2, 1, , D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
	}

	void D3D12MaterialImpl::Upload()
	{
		shaderData->Upload();
	}
	void D3D12MaterialImpl::CreateTextureResourceView(size_t i, ShaderRefProperty<Assets::Texture>* prop)
	{
	}
	/*
	void D3D12MaterialImpl::CreateTextureResourceView(size_t i, ShaderRefProperty<Assets::Texture>* prop)
	{
		if (!prop->IsEmpty()) {

			unsigned long long type = prop->GetPropertyDataTyped().GetTypeId();

			D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};


			if (type == Assets::Texture2D::TypeId())
			{
				auto a = std::dynamic_pointer_cast<D3D12::D3D12Texture2D>(prop->GetPropertyDataTyped().getImpl());

				srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
				srvDesc.Format = a->GetDXGIFormat();
				srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;

				srvDesc.Texture2D.MipLevels = 1;

				DX12RendererAPI::device->CreateShaderResourceView(a->GetResource().Get(), &srvDesc,
					table.GetDescriptorHandle(1+i));
			}
			else if (type == Assets::TextureCubeMap::TypeId())
			{
				auto a = std::dynamic_pointer_cast<D3D12::D3D12TextureCubeMap>(prop->GetPropertyDataTyped().getImpl());

				srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;
				srvDesc.Format = a->GetDXGIFormat();
				srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
				srvDesc.TextureCube.MipLevels = 1;
				srvDesc.Texture2D.MipLevels = 1;

				DX12RendererAPI::device->CreateShaderResourceView(a->GetResource().Get(), &srvDesc,
					table.GetDescriptorHandle(1 + i));
			}
		}

	}
	*/
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
