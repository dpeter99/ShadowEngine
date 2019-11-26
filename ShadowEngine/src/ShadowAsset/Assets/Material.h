#pragma once
#include "Core/Core.h"
#include "Core/SHObject.h"
#include "ShadowAsset/ShadowAsset.h"

#include "ShadowRenderer/Buffer.h"
#include "ShadowRenderer/Shader.h"
#include "ShadowRenderer/ShaderPropertySheet.h"

namespace ShadowEngine::Rendering {
	class ConstantBuffer;
}

namespace ShadowEngine::Assets {

	class MaterialImpl
	{
	public:
		static MaterialImpl* Create(Ref<Rendering::ShaderPropertySheet> propertySheet);

		virtual void Upload() = 0;
	};
	
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

		Ref<Rendering::ConstantBuffer> [[depricated]] shaderData;


		
		bool dirty = true;
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

		//Ref<Rendering::ConstantBuffer>& GetBuffer();

		Ref<MaterialImpl> getImpl();
		
		void UpdateBufferIfDirty();
		
		
		Material(const Ref<Rendering::Shader>& shader);

	};
}
