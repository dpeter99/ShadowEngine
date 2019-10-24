#include "shpch.h"
#include "Material.h"

namespace  ShadowEngine::Assets {
	Ref<ShaderPropertySheet>& Material::GetProperties()
	{
		return properties;
	}

	Material::Material(const Ref<Rendering::Shader>& shader)
	{
		this->shader = shader;
		
		this->properties.reset(shader->GetPropertiesCopy());
	}

}