#pragma once

#include "Common.h"
#include "D3D12DescriptorHeap.h"
#include "ShadowRenderer/ConstantBuffer.h"
#include "DX12RendererAPI.h"
#include "D3D12ConstantBuffer.h"
#include "ShadowAsset/Assets/Textures/Texture.h"

//#include "ShadowRenderer/MaterialImpl.h"

namespace  ShadowEngine::Rendering::D3D12 {


	//This should hold the:
	//Constant buffers
	//The textures
	class D3D12MaterialImpl : public Assets::MaterialImpl
	{
		Ref<ShaderPropertySheet> propertySheet;


		Ref<Rendering::ConstantBuffer> shaderData;

		//std::vector<Ref<D3D12Texture2D>> textures;
		
		DescriptorAllocation table;
		


		int rootSigIndex;
	public:
		D3D12MaterialImpl(Ref<ShaderPropertySheet> propertySheet);

		void BindMaterialData(Ref<CommandList> commandList);

		void Upload() override;
		void CreateTextureResourceView(size_t i, ShaderRefProperty<Assets::Texture>* prop);

		void UploadTextures();
	};

}

