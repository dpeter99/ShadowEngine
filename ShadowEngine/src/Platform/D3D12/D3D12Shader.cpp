#include "shpch.h"

#include "D3D12Shader.h"
#include "D3D12RendererAPI.h"

namespace ShadowEngine::Rendering::D3D12 {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShadowEngine::Rendering::ShaderDataType::Float:    return DXGI_FORMAT_R32_FLOAT;
		case ShadowEngine::Rendering::ShaderDataType::Float2:   return DXGI_FORMAT_R32G32_FLOAT;
		case ShadowEngine::Rendering::ShaderDataType::Float3:   return DXGI_FORMAT_R32G32B32_FLOAT;
		case ShadowEngine::Rendering::ShaderDataType::Float4:   return DXGI_FORMAT_R32G32B32A32_FLOAT;
		case ShadowEngine::Rendering::ShaderDataType::Mat3:     return ;
		case ShadowEngine::Rendering::ShaderDataType::Mat3:     return ;
		case ShadowEngine::Rendering::ShaderDataType::Mat4:     return GL_FLOAT;
		case ShadowEngine::Rendering::ShaderDataType::Int:      return GL_INT;
		case ShadowEngine::Rendering::ShaderDataType::Int2:     return GL_INT;
		case ShadowEngine::Rendering::ShaderDataType::Int3:     return GL_INT;
		case ShadowEngine::Rendering::ShaderDataType::Int4:     return GL_INT;
		case ShadowEngine::Rendering::ShaderDataType::Bool:     return DXGI_FORMAT_1;
		}

		SH_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}
	
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

	void D3D12Shader::ApplyToDescriptor(D3D12_GRAPHICS_PIPELINE_STATE_DESC& psoDesc) {
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

	D3D12_INPUT_LAYOUT_DESC& D3D12Shader::CreateInputDescriptor()
	{
		
	}

	void ApplyInputLaout()
	{
		
	}
	
	D3D12Shader::D3D12Shader(const std::string& VSfilePath, const std::string& PSfilePath)
	{
		blendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
		rasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
		depthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
		depthStencilState.DepthEnable = FALSE;
		depthStencilState.StencilEnable = FALSE;
		dsvFormat = DXGI_FORMAT_UNKNOWN;
		
		VertexShaderByteCode = LoadCso(VSfilePath);
		FragmentShaderByteCode = LoadCso(PSfilePath);
		
		//Load Root signature
		DX_API("Failed to create root signature")
		D3D12RendererAPI::device->CreateRootSignature(0, VertexShaderByteCode->GetBufferPointer(),
			VertexShaderByteCode->GetBufferSize(), IID_PPV_ARGS(rootSig.GetAddressOf()));


		ZeroMemory(&gpsoDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
		gpsoDesc.NumRenderTargets = 1;
		gpsoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		gpsoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
		gpsoDesc.InputLayout = D3D12RendererAPI::input_layout;
		ApplyToDescriptor(gpsoDesc);

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

		pipelineState = psoMan->Get(gpsoDesc);
		
	}

	
}
