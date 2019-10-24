#include "shpch.h"

#include "D3D12Shader.h"
#include "D3D12RendererAPI.h"
#include "ShadowRenderer/Vertex.h"

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

		ASSERT(file.is_open(), "Failed to open blob file: %s", filePath.c_str());

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
		rasterizerState.CullMode = D3D12_CULL_MODE_FRONT;
		depthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
		depthStencilState.DepthEnable = FALSE;
		depthStencilState.StencilEnable = FALSE;
		dsvFormat = DXGI_FORMAT_UNKNOWN;

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

	void D3D12Shader::Bind() const
	{
		
	}

	void D3D12Shader::Unbind() const
	{
		
	}
}
