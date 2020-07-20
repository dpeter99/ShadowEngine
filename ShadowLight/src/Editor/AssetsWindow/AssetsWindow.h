#pragma once
#include "../EditorWindow.h"

#include "ShadowAsset/AssetManager.h"

namespace ShadowLight::Editor {

	class AssetsWindow : public EditorWindow
	{
		bool active = true;

		AssetManager* assetManager = nullptr;
	public:
		void Draw() override;
	};

}
