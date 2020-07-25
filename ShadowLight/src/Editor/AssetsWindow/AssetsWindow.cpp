
#include "imgui.h"
#include "AssetsWindow.h"


#include "ShadowAsset/AssetManager.h"
#include "ShadowModules/ShadowModuleManager.h"

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
			ImGui::Text(var.getName().c_str());
		}

		ImGui::End();

	}

}
