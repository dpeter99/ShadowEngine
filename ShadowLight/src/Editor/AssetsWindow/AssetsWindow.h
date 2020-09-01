#pragma once
#include "../EditorWindow.h"

#include "Assets/AssetManager.h"

namespace ShadowLight::Editor {

	class AssetsWindow : public EditorWindow
	{
		bool active = true;

		ShadowEngine::Assets::AssetManager* assetManager = nullptr;
	public:
		void Draw() override;
	};

}
