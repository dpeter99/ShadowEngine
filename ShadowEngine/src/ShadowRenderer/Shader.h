#pragma once

#include <string>
#include "ShaderProperties/ShaderPropertySheet.h"
#include "Assets/ShadowAsset.h"

namespace ShadowEngine::Rendering {

	class Shader;

	class Shader_Impl {
	protected:
		Shader& asset;
	public:
		Shader_Impl(Shader& asset) : asset(asset)
		{
			
		}

		virtual void LoadShader(const std::string& VSFilePath, const std::string& PSFilePath, bool compiled = true) = 0;

		static Shader_Impl* Create(Shader& asset);
	};


	/// <summary>
	/// Represents a shared in the engine
	/// </summary>
	/// TODO: Make shaders assets
	class Shader : public ShadowEngine::Assets::ShadowAsset
	{
	private:
		friend class Shader_Impl;
	protected:
		/// <summary>
		/// This contains the list of properties that this shader has. This contains the default values for those peoperties
		/// </summary>
		ShaderPropertySheet properties;

		Ref<Shader_Impl> impl;

		
	public:
		virtual ~Shader() = default;

		ShaderPropertySheet* GetPropertiesCopy() const;
		
		ShaderPropertySheet& GetProperties() { return properties; }

		//virtual void Bind() const = 0;
		//virtual void Unbind() const = 0;

		[[deprecated("Use the asset pipeline")]]
		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);

		[[deprecated("Use the asset pipeline")]]
		static Shader* CreateFromCompiled(const std::string& VSfilePath, const std::string& PSfilePath);

		void LoadShader(const std::string& VSFilePath, const std::string& PSFilePath, bool compiled = true) { impl->LoadShader(VSFilePath, PSFilePath, compiled); };
		
		// Inherited via ShadowAsset
		void Load(SFF::SFFElement& root, Assets::FileSystem::Path path) override;

		
	};

}
