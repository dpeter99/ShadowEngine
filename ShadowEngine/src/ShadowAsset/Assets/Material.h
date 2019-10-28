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
	
	class Material : public ShadowAsset
	{
		SHObject_Base(Material)
	private:
		
		std::shared_ptr<ShadowEngine::Rendering::Shader> shader;

		Ref<Rendering::ShaderPropertySheet> properties;

		Ref<Rendering::ConstantBuffer> shaderData;
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

		Ref<Rendering::ConstantBuffer>& GetBuffer();
		void UpdateBufferIfDirty();
		
		
		Material(const Ref<Rendering::Shader>& shader);

	};
}
