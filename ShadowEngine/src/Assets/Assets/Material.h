#pragma once
#include "Core/Core.h"
#include "Core/SHObject.h"
#include "Assets/ShadowAsset.h"

#include "ShadowRenderer/Buffer.h"
#include "ShadowRenderer/Shader.h"
#include "ShadowRenderer/ShaderProperties/ShaderPropertySheet.h"
#include <Assets\Assets\Textures\Texture2D.h>

namespace ShadowEngine::Rendering {
	class ConstantBuffer;
}

namespace ShadowEngine::Assets {

	/// <summary>
	/// The actual render api implementation of materials.
	/// It should not be used by the user directly.
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

		/// <summary>
		/// The shader this material uses
		/// </summary>
		Ref<ShadowEngine::Rendering::Shader> shader;
		
		/// <summary>
		/// The properties sheet this material is using
		/// </summary>
		Ref<Rendering::ShaderPropertySheet> properties;

		/// <summary>
		/// Properties dirty
		/// </summary>
		/// Indicates if any of the non texture properties have changed.
		bool dirty = true;

		/// <summary>
		/// Textures dirty
		/// </summary>
		/// Indicates if any textures have changed
		bool texture_dirty = true;
	public:
		/// <summary>
		/// returns the property sheet
		/// </summary>
		/// <returns>The property sheet in use by this material</returns>
		Ref<Rendering::ShaderPropertySheet>& GetProperties();

		/// <summary>
		/// returns the shader used by this material
		/// </summary>
		/// <returns></returns>
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
				SH_CORE_WARN("No property named: '{0}' in shader: '{1}'", name, "....");
				return;
			}
			property->SetValue(value);
			//properties->UpdataStruct();
			texture_dirty = true;
		}

		void SetTexture2D(const std::string& name, Ref<Texture2D> value);

		Ref<MaterialImpl> getImpl();

		void UpdateBufferIfDirty();


		Material(const Ref<Rendering::Shader>& shader);

		void Load(SFF::SFFElement& root, FileSystem::Path path) override;
	};
}
