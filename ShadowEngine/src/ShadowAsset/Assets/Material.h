#pragma once
#include "Core/Core.h"
#include "Core/SHObject.h"
#include "ShadowAsset/ShadowAsset.h"

#include "ShadowRenderer/Buffer.h"
#include "ShadowRenderer/Shader.h"
#include "ShadowRenderer/ShaderPropertySheet.h"

namespace ShadowEngine::Assets {

	class Material : public ShadowAsset
	{
		SHObject_Base(Material)
	private:
		
		std::shared_ptr<ShadowEngine::Rendering::Shader> shader;

		Ref<ShaderPropertySheet> properties;
		
	public:
		Ref<ShaderPropertySheet>& GetProperties();
	
		
		Material(const Ref<Rendering::Shader>& shader);

	};
}
