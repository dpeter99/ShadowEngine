
#include "imgui.h"
#include "AssetsWindow.h"


#include "Assets/AssetManager.h"
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
			auto info = var.second;

			std::string text = std::string(info->getLoaded() ? ICON_FA_CHECK : ICON_FA_TIMES);
			text += " ";
			text += info->getPath();
			ImGui::Text(text.c_str());
		}

		ImGui::End();

	}

}
