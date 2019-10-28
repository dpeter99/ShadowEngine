#include "shpch.h"
#include "Material.h"
#include "ShadowRenderer/Vertex.h"
#include "ShadowRenderer/ConstantBuffer.h"

namespace  ShadowEngine::Assets {
	Ref<Rendering::ShaderPropertySheet>& Material::GetProperties()
	{
		return properties;
	}

	Ref<Rendering::Shader> Material::GetShader()
	{
		return this->shader;
	}

	Ref<Rendering::ConstantBuffer>& Material::GetBuffer()
	{
		return this->shaderData;
	}

	void Material::UpdateBufferIfDirty()
	{
		if(dirty)
		{
			this->shaderData->Upload();
			dirty = false;
		}
	}

	Material::Material(const Ref<Rendering::Shader>& shader)
	{
		this->shader = shader;
		
		this->properties.reset(shader->GetPropertiesCopy());
		
		this->shaderData = std::make_shared<Rendering::ConstantBuffer_ShaderPropertySheet>(properties);
	}

}
