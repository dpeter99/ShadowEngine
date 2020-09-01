#pragma once

#include <string>
#include "ShaderProperties/ShaderPropertySheet.h"
#include "Assets/ShadowAsset.h"

namespace ShadowEngine::Rendering {

	/// <summary>
	/// Represents a shared in the engine
	/// </summary>
	/// TODO: Make shaders assets
	class Shader : public ShadowEngine::Assets::ShadowAsset
	{
	protected:
		/// <summary>
		/// This contains the list of properties that this shader has. This contains the default values for those peoperties
		/// </summary>
		ShaderPropertySheet properties;
	public:
		virtual ~Shader() = default;

		ShaderPropertySheet* GetPropertiesCopy() const;
		
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
		static Shader* CreateFromCompiled(const std::string& VSfilePath, const std::string& PSfilePath);

		virtual void LoadShader(const std::string& VSFilePath, const std::string& PSFilePath, bool compiled = true) = 0;
		
		// Inherited via ShadowAsset
		void Load(SFF::SFFElement& root, Assets::FileSystem::Path path) override;
	};

}
