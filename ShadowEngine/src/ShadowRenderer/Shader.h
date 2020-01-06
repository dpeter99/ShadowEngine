#pragma once

#include <string>
#include "ShaderProperties/ShaderPropertySheet.h"

namespace ShadowEngine::Rendering {

	class Shader
	{
	protected:
		ShaderPropertySheet properties;
	public:
		virtual ~Shader() = default;

		ShaderPropertySheet* GetPropertiesCopy();
		
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
		static Shader* CreateFromCompiled(const std::string& VSfilePath, const std::string& PSfilePath);
	};

}
