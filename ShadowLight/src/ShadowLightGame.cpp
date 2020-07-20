#include "ShadowLightGame.h"

#include "Log.h"
#include "Core/ShadowApplication.h"

#include "Editor/EditorModule.h"



ShadowEngine::IGame* entryPoint()
{
	return new ShadowLight::ShadowLightGame();
}

ShadowEngine::SetupFunction _setupFunc = entryPoint;

namespace ShadowLight {
	ShadowLightGame::ShadowLightGame()
	{
		app = &ShadowEngine::ShadowApplication::Get();
	}

	void ShadowLightGame::Init()
	{

		SH_INFO("Game Init");
		
		auto& mm = app->GetModuleManager();
		mm.PushModule(new Editor::EditorModule());
	}

	void ShadowLightGame::Start()
	{
	}

	void ShadowLightGame::Stop()
	{
	}

}