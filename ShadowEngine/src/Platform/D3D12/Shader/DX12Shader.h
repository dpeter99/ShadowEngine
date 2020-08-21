#pragma once
#include "ShadowRenderer/Shader.h"

#include "../Common.h"

namespace ShadowEngine {
	namespace Rendering {
		class BufferLayout;
	}
}

namespace ShadowEngine::Rendering::D3D12 {

	/// <summary>
	/// Represents the shader byte code that can be used to draw.
	/// </summary>
	///
	/// 
	/// DX12Shader is the type ShadowEngine uses to represent byte code that has been compiled form HLSL to be used in
	/// the Dx12 renderer. Users should not handle DX12Shader's by itself,
	/// but the ShadowEngine::Rendering::Shader class and it's Create function to make sure the shader class is made for the right render API.
	/// Sample Usage:
	/// <code>
	///     var shader = ShadowEngine::Rendering::Shader::CreateFromCompiled("Shaders/Default-VS.cso", "Shaders/Default-FS.cso");
	/// </code>
	class DX12Shader :
		public Shader
	{
		com_ptr<ID3DBlob> VertexShaderByteCode{ nullptr };
		com_ptr<ID3DBlob> FragmentShaderByteCode{ nullptr };

		com_ptr<ID3D12RootSignature> rootSig{ nullptr };

		D3D12_BLEND_DESC blendState{};
		D3D12_RASTERIZER_DESC rasterizerState{};
		D3D12_DEPTH_STENCIL_DESC depthStencilState{};
		DXGI_FORMAT dsvFormat;

		com_ptr<ID3D12PipelineState> pipelineState{ nullptr };
		D3D12_GRAPHICS_PIPELINE_STATE_DESC gpsoDesc{};

		com_ptr<ID3D12ShaderReflection> vsReflection;
		com_ptr<ID3D12ShaderReflection> gsReflection;
		com_ptr<ID3D12ShaderReflection> psReflection;
		com_ptr<ID3D12RootSignatureDeserializer> rsDeserializer;

		int materialDataIndex;
		
	private:

		/// <summary>
		/// Loads a HLSL shader code from a compiled cso file
		/// </summary>
		/// <param name="VSfilePath">Path to the code file (.cso)</param>
		/// <returns>Com pointer to the code blob</returns>
		static com_ptr<ID3DBlob> DX12Shader::LoadCso(const std::string& VSfilePath);

		/// <summary>
		/// Populates a Pipeline state Descriptor for this shader
		/// </summary>
		/// <param name="psoDesc">The Pipeline State Descriptor to populate</param>
		void CreatePipelineDescriptor(D3D12_GRAPHICS_PIPELINE_STATE_DESC& psoDesc) const;

		/// <summary>
		/// Creates an Input Layout descriptor form BufferLayout
		/// </summary>
		/// <param name="layout">The buffer layout to be converted</param>
		/// <returns>The Input Layout</returns>
		static D3D12_INPUT_LAYOUT_DESC CreateInputDescriptor(BufferLayout& layout);
		
		void ExtractProperties [[deprecated]] ();

		void ExtractCBProps(D3D12_SHADER_INPUT_BIND_DESC binding);

		void Props();


	public:

		/// <summary>
		/// Constructor for D3D12 Shader.
		/// </summary>
		/// <param name="VSfilePath">File path to the Compiled HLSL Vertex shader</param>
		/// <param name="PSfilePath">File path to the Compiled HLSL Fragment shader</param>
		DX12Shader(const std::string& VSfilePath, const std::string& PSfilePath);
		virtual ~DX12Shader();

		/**
		 * Used to get the pipe line state object for the represented shader code.
		 * Returns the default Dx12 ID3D12PipelineState object
		 *
		 * \brief Returns the pipeline state
		 * \return The com pointer of the root signature
		 */
		com_ptr<ID3D12PipelineState> GetPipelineState();

		/**
		* Used to get the root signature of the represented shader code.
		* Returns the default Dx12 ID3D12RootSignature object
		*
		* \brief Returns the Root signature
		* \return The com pointer of the root signature
		*/
		com_ptr<ID3D12RootSignature> GetRootSignature();
		
		int GetMaterialSlotIndex();
		
		virtual void Bind() const;
		virtual void Unbind() const;

		void LoadShader(const std::string& VSFilePath, const std::string& PSFilePath, bool compiled = true) override;
	};

}
