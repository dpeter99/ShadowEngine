#pragma once
#include "Core/Core.h"
#include "Core/SHObject.h"
#include "ShadowAsset/ShadowAsset.h"

#include "ShadowRenderer/Buffer.h"
#include "ShadowRenderer/Shader.h"
#include "ShadowRenderer/ShaderProperties/ShaderPropertySheet.h"

namespace ShadowEngine::Rendering {
	class ConstantBuffer;
}

namespace ShadowEngine::Assets {

	/// <summary>
	/// The actual render api implementation of materials
	/// It shuld not be used by the user directly, but as the field of the Material Asset
	/// </summary>
	class MaterialImpl
	{
	public:
		static MaterialImpl* Create(Ref<Rendering::ShaderPropertySheet> propertySheet);

		virtual void Upload() = 0;
		virtual void UploadTextures() = 0;
	};
	
	/// <summary>
	/// Material asset
	/// A material is the asset that we assign to the meshes. It specifies all the values that will be used for drawing the mesh.
	/// Like: Textures, floats, positions etc..
	/// 
	/// This contains the renderer implementation and the asset information for this material.
	/// </summary>
	class Material : public ShadowAsset
	{
		SHObject_Base(Material)
	private:
			Ref<MaterialImpl> impl;
		
	private:

		
		/**
		 * \brief The shader this material uses
		 */
		std::shared_ptr<ShadowEngine::Rendering::Shader> shader;

		
		/**
		 * \brief The properties sheet this material is using
		 */
		Ref<Rendering::ShaderPropertySheet> properties;

		//Ref<Rendering::ConstantBuffer> [[depricated]] shaderData;


		
		bool dirty = true;
		bool texture_dirty = true;
	public:		
		Ref<Rendering::ShaderPropertySheet>& GetProperties();
		Ref<Rendering::Shader> GetShader();

		template<class T>
		void SetProperty(const std::string& name, const T& value)
		{
			auto property = properties->GetProperty<T>(name);
			if (property == nullptr) {
				SH_CORE_WARN("No property named: %s", name);
				return;
			}
			property->SetValue(value);
			properties->UpdataStruct();
			dirty = true;
		}

		template<class T>
		void SetTexture(const std::string& name, Ref<T> value) {

			auto property = properties->GetTexture<T>(name);
			if (property == nullptr) {
				SH_CORE_WARN("No property named: %s", name);
				return;
			}
			property->SetValue(value);
			//properties->UpdataStruct();
			texture_dirty = true;
		}

		//Ref<Rendering::ConstantBuffer>& GetBuffer();

		Ref<MaterialImpl> getImpl();
		
		void UpdateBufferIfDirty();
		
		
		Material(const Ref<Rendering::Shader>& shader);

	};
}
