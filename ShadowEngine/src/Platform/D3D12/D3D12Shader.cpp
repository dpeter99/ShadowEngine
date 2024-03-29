﻿#include "shpch.h"

#include "D3D12Shader.h"
#include "D3D12RendererAPI.h"
#include "ShadowRenderer/DataStructs.h"
#include "ShadowAsset/Assets/Textures/Texture.h"
#include "ShadowAsset/Assets/Textures/Texture2D.h"
#include "ShadowAsset/Assets/Textures/TextureCubeMap.h"

namespace ShadowEngine::Rendering::D3D12 {

	static DXGI_FORMAT ShaderDataTypeToD3D12BaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShadowEngine::Rendering::ShaderDataType::Float:    return DXGI_FORMAT_R32_FLOAT;
		case ShadowEngine::Rendering::ShaderDataType::Float2:   return DXGI_FORMAT_R32G32_FLOAT;
		case ShadowEngine::Rendering::ShaderDataType::Float3:   return DXGI_FORMAT_R32G32B32_FLOAT;
		case ShadowEngine::Rendering::ShaderDataType::Float4:   return DXGI_FORMAT_R32G32B32A32_FLOAT;
		case ShadowEngine::Rendering::ShaderDataType::Int:      return DXGI_FORMAT_R32_SINT;
		case ShadowEngine::Rendering::ShaderDataType::Int2:     return DXGI_FORMAT_R32G32_SINT;
		case ShadowEngine::Rendering::ShaderDataType::Int3:     return DXGI_FORMAT_R32G32B32_SINT;
		case ShadowEngine::Rendering::ShaderDataType::Int4:     return DXGI_FORMAT_R32G32B32A32_SINT;
		}

		SH_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return DXGI_FORMAT_UNKNOWN;
	}

	/**
	 * \brief Loads a HLSL shader code from a compiled cso file
	 * \param VSfilePath Path to the code file (.cso)
	 * \return Com pointer to the code blob
	 */
	com_ptr<ID3DBlob> D3D12Shader::LoadCso(const std::string& VSfilePath)
	{
		std::ifstream file{ VSfilePath, std::ios::binary | std::ios::ate };

		ASSERT(file.is_open(), "Failed to open blob file: %s", VSfilePath.c_str());

		std::streamsize size = file.tellg();

		file.seekg(0, std::ios::beg);

		com_ptr<ID3DBlob> shaderByteCode{ nullptr };

		DX_API("Failed to allocate memory for blob")
			D3DCreateBlob((size_t)size, shaderByteCode.GetAddressOf());

		if (file.read(reinterpret_cast<char*>(shaderByteCode->GetBufferPointer()), size)) {
			return shaderByteCode;
		}
		else {
			throw std::exception{ "Failed to load CSO file" };
		}
	}

	/**
	 * \brief Populates a Pipeline state Descriptor for this shader
	 * \param psoDesc The Pipeline State Descriptor to populate
	 */
	void D3D12Shader::CreatePipelineDescriptor(D3D12_GRAPHICS_PIPELINE_STATE_DESC& psoDesc) const
	{
		psoDesc.NumRenderTargets = 1;
		psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
		psoDesc.InputLayout = CreateInputDescriptor(Vertex::input_layout);

		psoDesc.pRootSignature = rootSig.Get();
		psoDesc.VS = CD3DX12_SHADER_BYTECODE(VertexShaderByteCode.Get());
		/*
		if (geometryShader != nullptr) {
			psoDesc.GS = CD3DX12_SHADER_BYTECODE(geometryShader.Get());
		}
		*/
		psoDesc.PS = CD3DX12_SHADER_BYTECODE(FragmentShaderByteCode.Get());
		psoDesc.BlendState = blendState;
		psoDesc.RasterizerState = rasterizerState;
		psoDesc.DepthStencilState = depthStencilState;
		psoDesc.DSVFormat = dsvFormat;
		psoDesc.SampleDesc.Count = 1;
		psoDesc.SampleDesc.Quality = 0;
		psoDesc.SampleMask = UINT_MAX;
	}

	/**
	 * \brief Creates a Input Layout descriptor form BufferLayout
	 * \param layout The buffer layout to be converted
	 * \return The Input Layout
	 */
	D3D12_INPUT_LAYOUT_DESC D3D12Shader::CreateInputDescriptor(BufferLayout& layout)
	{
		D3D12_INPUT_LAYOUT_DESC layout_desc;

		auto elements = new std::vector<D3D12_INPUT_ELEMENT_DESC>();

		for (const auto& element : layout)
		{
			D3D12_INPUT_ELEMENT_DESC e;
			e.SemanticName = element.Name.c_str();
			e.SemanticIndex = 0;
			e.Format = ShaderDataTypeToD3D12BaseType(element.Type);
			e.InputSlot = 0;
			e.AlignedByteOffset = element.Offset;
			e.InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
			e.InstanceDataStepRate = 0;

			elements->push_back(e);
		}

		layout_desc.NumElements = elements->size();
		layout_desc.pInputElementDescs = &(elements->at(0));
		return layout_desc;
	}

	//old
	void D3D12Shader::ExtractProperties()
	{
		//################################################################
		//Extract the Material data form the shader
		//################################################################

		//Get the shader description
		D3D12_SHADER_DESC shader_desc;
		psReflection->GetDesc(&shader_desc);

		//Get the correctly named Constant buffer reflection
		//We use this to identify the Descriptor table containing the data concerning the material
		//Like: floats, textures etc...
		ID3D12ShaderReflectionConstantBuffer* a = psReflection->GetConstantBufferByName("MaterialData");

		//The description of the actual contents of the buffer Constant buffer
		D3D12_SHADER_BUFFER_DESC desc;
		a->GetDesc(&desc);


		//We get the description of the buffer binding (binding pos etc.)
		D3D12_SHADER_INPUT_BIND_DESC bindDesc;
		psReflection->GetResourceBindingDescByName("MaterialData", &bindDesc);


		//Find the descriptor table that holds this input binding
		const D3D12_ROOT_SIGNATURE_DESC& rootSignatureDesc = *(rsDeserializer->GetRootSignatureDesc());

		for (unsigned int i = 0; i < rootSignatureDesc.NumParameters; ++i) {

			const D3D12_ROOT_PARAMETER& param = rootSignatureDesc.pParameters[i];

			//This is a Descriptor table
			/*
			if (param.ParameterType == D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE) {

				//Empty descriptor Table
				if (param.DescriptorTable.NumDescriptorRanges == 0) {
					continue;
				}
				bool correct = false;

				//We iterate over all the descriptor ranges to find the one containing our "MaterialData" CB
				for (int j = 0; j < param.DescriptorTable.NumDescriptorRanges; ++j)
				{
					D3D12_DESCRIPTOR_RANGE range = param.DescriptorTable.pDescriptorRanges[j];

					//Check if our CB is in this range
					if(range.RangeType == D3D12_DESCRIPTOR_RANGE_TYPE_CBV &&
						range.BaseShaderRegister <= bindDesc.BindPoint &&
						range.NumDescriptors + range.BaseShaderRegister -1 >= bindDesc.BindPoint &&
						range.RegisterSpace == bindDesc.Space)
					{
						correct = true;
						break;
					}

				}
				if (correct) {
					//We iterate over all the descriptor ranges to extract the parameters
					for (int j = 0; j < param.DescriptorTable.NumDescriptorRanges; ++j)
					{
						D3D12_DESCRIPTOR_RANGE range = param.DescriptorTable.pDescriptorRanges[j];

						//Check if our CB is in this range
						if (range.RangeType == D3D12_DESCRIPTOR_RANGE_TYPE_SRV)
						{
							D3D12_SHADER_INPUT_BIND_DESC parameter_binding_desc;
							psReflection->GetResourceBindingDesc(1, &parameter_binding_desc);
							//psReflection->GetResourceBindingDescByName("txt", &parameter_binding_desc);


							std::cout << "asd";
						}
					}
				}

			}
			else*/
			if (param.ParameterType == D3D12_ROOT_PARAMETER_TYPE_CBV &&
				param.Descriptor.ShaderRegister == bindDesc.BindPoint &&
				param.Descriptor.RegisterSpace == bindDesc.Space)
			{
				this->materialDataIndex = i;
				break;
			}
		}


		//Extract the material data variables
		for (int j = 0; j < desc.Variables; ++j)
		{
			ID3D12ShaderReflectionVariable* var = a->GetVariableByIndex(j);

			ID3D12ShaderReflectionType* type = var->GetType();
			D3D12_SHADER_TYPE_DESC type_desc;

			D3D12_SHADER_VARIABLE_DESC var_desc;
			var->GetDesc(&var_desc);

			type->GetDesc(&type_desc);

			if (strcmp(type_desc.Name, "float4") == 0)
			{
				this->properties.AddProperty(new ShaderProperty<glm::vec4>(var_desc.Name));
			}
		}



		properties.UpdataStruct();
	}

	void D3D12Shader::ExtractCBProps(D3D12_SHADER_INPUT_BIND_DESC binding) {

		if (binding.Type != D3D_SIT_CBUFFER) {
			return;
		}

		ID3D12ShaderReflectionConstantBuffer* a = psReflection->GetConstantBufferByName(binding.Name);

		//The description of the actual contents of the Constant buffer
		D3D12_SHADER_BUFFER_DESC desc;
		a->GetDesc(&desc);

		//Extract the material data variables
		for (int j = 0; j < desc.Variables; ++j)
		{
			ID3D12ShaderReflectionVariable* var = a->GetVariableByIndex(j);

			ID3D12ShaderReflectionType* type = var->GetType();
			D3D12_SHADER_TYPE_DESC type_desc;

			D3D12_SHADER_VARIABLE_DESC var_desc;
			var->GetDesc(&var_desc);

			type->GetDesc(&type_desc);

			if (strcmp(type_desc.Name, "float4") == 0)
			{
				this->properties.AddProperty(new ShaderProperty<glm::vec4>(var_desc.Name));
			}
		}
	}

	void D3D12Shader::Props() {

		//################################################################
		//Extract the Material data form the shader
		//################################################################

		//Get the shader description
		D3D12_SHADER_DESC shader_desc;
		psReflection->GetDesc(&shader_desc);

		std::vector<D3D12_SHADER_INPUT_BIND_DESC> parameters;
		int descriptorTableParameterIndex = -1;

		bool matCB = false;

		for (size_t i = 0; i < shader_desc.BoundResources; i++)
		{
			D3D12_SHADER_INPUT_BIND_DESC binding_desc;
			psReflection->GetResourceBindingDesc(i, &binding_desc);
			bool matdata = false;
			if (std::string(binding_desc.Name).rfind("Mat_", 0) == 0) {
				matdata = true;
				parameters.push_back(binding_desc);

				if (binding_desc.Type == D3D_SIT_CBUFFER) {
					SH_ASSERT(!matCB, "There can only be one material CB");

					matCB = true;

					ExtractCBProps(binding_desc);
				}
				else if (binding_desc.Type == D3D_SIT_TEXTURE) {
					switch (binding_desc.Dimension)
					{
					case(D3D_SRV_DIMENSION_TEXTURE2D):
						properties.AddTexture(new ShadowEngine::Rendering::ShaderRefProperty<Assets::Texture2D>(binding_desc.Name));
						break;
					case(D3D_SRV_DIMENSION_TEXTURECUBE):
						properties.AddTexture(new ShadowEngine::Rendering::ShaderRefProperty<Assets::TextureCubeMap>(binding_desc.Name));
						break;
					default:
						break;
					}
				}
			}

			//Debug
#ifdef DX12_DEBUG
			{

				std::cout << "Binding: Name:" << binding_desc.Name << std::endl;

				{
					std::string type = "Unknown";
					switch (binding_desc.Type)
					{
					case(D3D_SIT_CBUFFER):
						type = "D3D_SIT_CBUFFER";
						break;
					case(D3D_SIT_TBUFFER):
						type = "D3D_SIT_TBUFFER";
						break;
					case(D3D_SIT_TEXTURE):
						type = "D3D_SIT_TEXTURE";
						break;
					case(D3D_SIT_SAMPLER):
						type = "D3D_SIT_SAMPLER";
						break;
					default:
						break;
					}

					std::cout << "\t Type: " << type << std::endl;
				}

				std::cout << "\t BindPoint: " << binding_desc.BindPoint << std::endl;
				std::cout << "\t BindCount: " << binding_desc.BindCount << std::endl;
				std::cout << "\t Space: " << binding_desc.Space << std::endl;
				std::cout << "\t Dim: " << binding_desc.Dimension << std::endl;
				std::wcout << "\t Material Data: " << (matdata ? "OK" : "NOP") << std::endl;

			}
#endif
		}


		//Extract the rood signature
		const D3D12_ROOT_SIGNATURE_DESC& rootSignatureDesc = *(rsDeserializer->GetRootSignatureDesc());

#ifdef DX12_DEBUG
		std::cout << "RootSig: " << std::endl;
#endif

		for (size_t i = 0; i < rootSignatureDesc.NumParameters; i++)
		{
			D3D12_ROOT_PARAMETER param = rootSignatureDesc.pParameters[i];

			//Debug info
#ifdef DX12_DEBUG
			{
				std::string type = "Unknown";

				switch (param.ParameterType)
				{
				case(D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE):
					type = "D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE";
					break;
				case(D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS):
					type = "D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS";
					break;
				case(D3D12_ROOT_PARAMETER_TYPE_CBV):
					type = "D3D12_ROOT_PARAMETER_TYPE_CBV";
					break;
				case(D3D12_ROOT_PARAMETER_TYPE_SRV):
					type = "D3D12_ROOT_PARAMETER_TYPE_SRV";
					break;
				case(D3D12_ROOT_PARAMETER_TYPE_UAV):
					type = "D3D12_ROOT_PARAMETER_TYPE_UAV";
					break;
				default:
					break;
				}


				std::cout << "\tParameter: Type: " << type << std::endl;

			}
#endif
			
			if (param.ParameterType == D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE) {

				//Debug Info
#ifdef DX12_DEBUG
				{
					std::cout << "\t\t Number of descriptors: " << param.DescriptorTable.NumDescriptorRanges << std::endl;
					for (size_t i = 0; i < param.DescriptorTable.NumDescriptorRanges; i++)
					{
						D3D12_DESCRIPTOR_RANGE range = param.DescriptorTable.pDescriptorRanges[i];

						{
							std::string type = "Unknown";

							switch (range.RangeType)
							{
							case(D3D12_DESCRIPTOR_RANGE_TYPE_SRV):
								type = "D3D12_DESCRIPTOR_RANGE_TYPE_SRV";
								break;
							case(D3D12_DESCRIPTOR_RANGE_TYPE_UAV):
								type = "D3D12_DESCRIPTOR_RANGE_TYPE_UAV";
								break;
							case(D3D12_DESCRIPTOR_RANGE_TYPE_CBV):
								type = "D3D12_DESCRIPTOR_RANGE_TYPE_CBV";
								break;
							case(D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER):
								type = "D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER";
								break;
							default:
								break;
							}

							std::cout << "\t\t Descriptor: Type: " << type << std::endl;
							std::cout << "\t\t\t Base Shader Register: " << range.BaseShaderRegister << std::endl;
							std::cout << "\t\t\t Register space: " << range.RegisterSpace << std::endl;
							std::cout << "\t\t\t Count: " << range.NumDescriptors << std::endl;
						}
					}
				}
#endif

				for (size_t j = 0; j < param.DescriptorTable.NumDescriptorRanges; j++)
				{
					D3D12_DESCRIPTOR_RANGE range = param.DescriptorTable.pDescriptorRanges[j];

					for each (auto & matBinding in parameters)
					{
						if (((range.RangeType == D3D12_DESCRIPTOR_RANGE_TYPE_CBV && matBinding.Type == D3D_SIT_CBUFFER) ||
							(range.RangeType == D3D12_DESCRIPTOR_RANGE_TYPE_SRV && matBinding.Type == D3D_SIT_TEXTURE)) &&
							range.BaseShaderRegister <= matBinding.BindPoint &&
							range.BaseShaderRegister + range.NumDescriptors >= matBinding.BindPoint &&
							range.RegisterSpace == matBinding.Space)
						{
							//SH_CORE_INFO("Found");
							if (descriptorTableParameterIndex == -1) {
								descriptorTableParameterIndex = i;
							}
							else if (descriptorTableParameterIndex != i) {
								SH_CORE_ERROR("All material data should be in the same descriptor table");
							}
						}
					}
				}

			}
			else if (param.ParameterType == D3D12_ROOT_PARAMETER_TYPE_CBV) {

				//Debug info
#ifdef DX12_DEBUG
				{
					std::cout << "\t\t Register Space: " << param.Descriptor.RegisterSpace << std::endl;
					std::cout << "\t\t Shader Register: " << param.Descriptor.ShaderRegister << std::endl;
				}
#endif

				for each (auto & matBinding in parameters)
				{
					if (((param.ParameterType == D3D12_ROOT_PARAMETER_TYPE_CBV && matBinding.Type == D3D_SIT_CBUFFER) ||
						(param.ParameterType == D3D12_ROOT_PARAMETER_TYPE_SRV && matBinding.Type == D3D_SIT_TEXTURE)) &&
						param.Descriptor.ShaderRegister == matBinding.BindPoint &&
						param.Descriptor.RegisterSpace == matBinding.Space)
					{
						SH_CORE_ERROR("Material data CB must be in a Descriptor table");
					}
				}


			}
		}

		//std::cout << properties.ToString();

	}

	/**
	 * \brief Constructor for D3D12 Shaders.
	 * \param VSfilePath File path to the Compiled HLSL Vertex shader
	 * \param PSfilePath File path to the Compiled HLSL Fragment shader
	 */
	D3D12Shader::D3D12Shader(const std::string& VSfilePath, const std::string& PSfilePath)
	{
		//Load in the default values for now
		blendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
		rasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
		rasterizerState.CullMode = D3D12_CULL_MODE_NONE;
		
		depthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
		depthStencilState.DepthEnable = TRUE;
		depthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
		depthStencilState.StencilEnable = FALSE;
		dsvFormat = DXGI_FORMAT_D32_FLOAT;


		//Load Up the shader codes
		VertexShaderByteCode = LoadCso(VSfilePath);
		FragmentShaderByteCode = LoadCso(PSfilePath);

		//Load Root signature
		DX_API("Failed to create root signature")
			D3D12RendererAPI::device->CreateRootSignature(0, VertexShaderByteCode->GetBufferPointer(),
				VertexShaderByteCode->GetBufferSize(), IID_PPV_ARGS(rootSig.GetAddressOf()));


		//Create the Pipeline State Descriptor
		ZeroMemory(&gpsoDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
		CreatePipelineDescriptor(gpsoDesc);


		DX_API("Failed to reflect vertex shader")
			D3DReflect(gpsoDesc.VS.pShaderBytecode, gpsoDesc.VS.BytecodeLength, IID_PPV_ARGS(vsReflection.GetAddressOf()));

		DX_API("Failed to reflect pixel shader")
			D3DReflect(gpsoDesc.PS.pShaderBytecode, gpsoDesc.PS.BytecodeLength, IID_PPV_ARGS(psReflection.GetAddressOf()));

		if (gpsoDesc.GS.pShaderBytecode != nullptr) {
			DX_API("Failed to reflect geometry shader")
				D3DReflect(gpsoDesc.GS.pShaderBytecode, gpsoDesc.GS.BytecodeLength, IID_PPV_ARGS(gsReflection.GetAddressOf()));
		}

		DX_API("Failed to deserialize root signature")
			D3D12CreateRootSignatureDeserializer(gpsoDesc.VS.pShaderBytecode, gpsoDesc.VS.BytecodeLength, IID_PPV_ARGS(rsDeserializer.GetAddressOf()));

		//Create the pipeline state object from the descriptor
		com_ptr<ID3D12PipelineState> pso{ nullptr };

		DX_API("PSOManager: Failed to create GPSO")
			D3D12RendererAPI::device->CreateGraphicsPipelineState(&gpsoDesc, IID_PPV_ARGS(pso.GetAddressOf()));

		pipelineState = pso;

		Props();
		//ExtractProperties();
	}

	D3D12Shader::~D3D12Shader()
	{

	}

	com_ptr<ID3D12PipelineState> D3D12Shader::GetPipelineState()
	{
		return pipelineState;
	}

	com_ptr<ID3D12RootSignature> D3D12Shader::GetRootSignature()
	{
		return rootSig;
	}

	int D3D12Shader::GetMaterialSlotIndex()
	{
		return materialDataIndex;
	}

	void D3D12Shader::Bind() const
	{

	}

	void D3D12Shader::Unbind() const
	{

	}


}
