#include "shpch.h"
#include "Material.h"
#include "ShadowRenderer/DataStructs.h"
#include "ShadowRenderer/ConstantBuffer.h"
#include "ShadowRenderer/Renderer.h"
#include "Platform/D3D12/D3D12MaterialImpl.h"

namespace  ShadowEngine::Assets {
	MaterialImpl* MaterialImpl::Create(Ref<Rendering::ShaderPropertySheet> propertySheet)
	{
		switch (ShadowEngine::Rendering::Renderer::GetAPI())
		{
		case Rendering::RendererAPI::API::None: SH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case Rendering::RendererAPI::API::D3D12: return (MaterialImpl*) new ShadowEngine::Rendering::D3D12::D3D12MaterialImpl(propertySheet);
		}

		SH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Rendering::ShaderPropertySheet>& Material::GetProperties()
	{
		return properties;
	}

	Ref<Rendering::Shader> Material::GetShader()
	{
		return this->shader;
	}

	Ref<MaterialImpl> Material::getImpl()
	{
		return impl;
	}

	void Material::UpdateBufferIfDirty()
	{
		if(dirty)
		{
			this->impl->Upload();
			dirty = false;
		}

		if (texture_dirty) {
			this->impl->UploadTextures();
			texture_dirty = false;
		}
	}

	Material::Material(const Ref<Rendering::Shader>& shader)
	{
		this->shader = shader;
		
		this->properties.reset(shader->GetPropertiesCopy());
		
		//this->shaderData = std::make_shared<Rendering::ConstantBuffer_ShaderPropertySheet>(properties);

		
		impl.reset(MaterialImpl::Create(properties));
		
	}

	void Material::Load(SFF::SFFElement& root, FileSystem::Path path)
	{
	}
}
