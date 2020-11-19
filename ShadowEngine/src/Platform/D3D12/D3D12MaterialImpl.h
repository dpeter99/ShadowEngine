#pragma once

#include "Common.h"
#include "D3D12DescriptorHeap.h"
#include "ShadowRenderer/ConstantBuffer.h"
#include "DX12RendererAPI.h"
#include "Buffers/DX12ConstantBuffer.h"
#include "Assets/Assets/Textures/Texture.h"

//#include "ShadowRenderer/MaterialImpl.h"

namespace  ShadowEngine::Rendering::D3D12 {


	//This should hold the:
	//Constant buffers
	//The textures
	
	class D3D12MaterialImpl : public Assets::MaterialImpl
	{
		/// <summary>
		/// The property sheet containing all of the data for this material
		/// </summary>
		Ref<ShaderPropertySheet> propertySheet;

		/// <summary>
		/// The constant buffer that has the non texture data for this material
		/// </summary>
		/// This buffer holds the general data for the sahder like floats
		/// They are all in a single constatnt buffer and uploaded if the data is marked as dirty
		Ref<Rendering::ConstantBuffer> shaderData;

		Ref<DX12ConstantBuffer> dx12_buffer;

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

