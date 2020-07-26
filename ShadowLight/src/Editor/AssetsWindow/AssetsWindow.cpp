
#include "imgui.h"
#include "AssetsWindow.h"


#include "ShadowAsset/AssetManager.h"
#include "ShadowModules/ShadowModuleManager.h"

#include "ImGui/IconsFontAwesome5.h"

namespace ShadowLight::Editor {

	void AssetsWindow::Draw()
	{
		if (assetManager == nullptr) {
			auto* mm = ShadowEngine::ShadowModuleManager::instance;
			assetManager = mm->GetModuleByType<ShadowEngine::Assets::AssetManager>();
		}
		
		ImGui::Begin("Assets", &active, ImGuiWindowFlags_None);

		for each (auto& var in assetManager->knownAssets)
		{
			std::string text = std::string(var.getLoaded() ? ICON_FA_CHECK : ICON_FA_TIMES) + " " + var.getName();
			ImGui::Text(text.c_str());
		}

		ImGui::End();

	}

}
