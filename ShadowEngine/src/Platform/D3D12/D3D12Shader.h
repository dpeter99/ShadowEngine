#pragma once
#include "ShadowRenderer/Shader.h"

#include "Common.h"

namespace ShadowEngine {
	namespace Rendering {
		class BufferLayout;
	}
}

namespace ShadowEngine::Rendering::D3D12 {

	class D3D12Shader :
		public Shader
	{
		com_ptr<ID3DBlob> VertexShaderByteCode{ nullptr };
		com_ptr<ID3DBlob> FragmentShaderByteCode{ nullptr };

		com_ptr<ID3D12RootSignature> rootSig{ nullptr };

		D3D12_BLEND_DESC blendState{};
		D3D12_RASTERIZER_DESC rasterizerState{};
		D3D12_DEPTH_STENCIL_DESC depthStencilState{};
		DXGI_FORMAT dsvFormat;

		com_ptr<ID3D12PipelineState> pipelineState;
		D3D12_GRAPHICS_PIPELINE_STATE_DESC gpsoDesc{};

		com_ptr<ID3D12ShaderReflection> vsReflection;
		com_ptr<ID3D12ShaderReflection> gsReflection;
		com_ptr<ID3D12ShaderReflection> psReflection;
		com_ptr<ID3D12RootSignatureDeserializer> rsDeserializer;
		
	public:
		D3D12Shader(const std::string& VSfilePath, const std::string& PSfilePath);
		virtual ~D3D12Shader();

		static com_ptr<ID3DBlob> D3D12Shader::LoadCso(const std::string& VSfilePath);
		void CreatePipelineDescriptor(D3D12_GRAPHICS_PIPELINE_STATE_DESC& psoDesc) const;
		static D3D12_INPUT_LAYOUT_DESC& CreateInputDescriptor(BufferLayout& layout);


		virtual void Bind() const;
		virtual void Unbind() const;
	};

}
