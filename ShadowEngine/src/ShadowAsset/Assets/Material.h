#pragma once
#include "Core/Core.h"
#include "Core/SHObject.h"
#include "ShadowAsset/ShadowAsset.h"

#include "ShadowRenderer/Buffer.h"
#include "ShadowRenderer/Shader.h"

namespace ShadowEngine::Assets {

	class Material : public ShadowAsset
	{
		SHObject_Base(Material)
	private:
		
		std::shared_ptr<ShadowEngine::Rendering::Shader> shader;

	public:

		
		Material(Ref<Rendering::Shader> shader);
		
	};
}
