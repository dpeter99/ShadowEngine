#include "shpch.h"

#include "ShadowApplication.h"

#include "IGame.h"
#include "ShadowModules/ShadowModuleManager.h"
#include "ShadowMap/ShadowWorld.h"
#include "ShadowAsset/AssetManager.h"
#include "ShadowMap/ShadowMapRenderer.h"
#include "ShadowEvents/ShadowEventManager.h"
#include "Platform/SDL/SDLModule.h"
#include "ImGui/ImGuiModule.h"
#include "glad/glad.h"
#include "ShadowMath/Vector2float.h"
#include "ShadowTime.h"
#include "ShadowInput/ShadowActionSystem.h"
#include "Debug/Debug.h"
#include "ShadowRenderer/Renderer.h"

#include "../TestRenderer.h"

#include "ShadowScene/TestScene.h"
#include "EntitySystem/EntitySystem.h"

namespace ShadowEngine {

	ShadowApplication* ShadowApplication::instance = nullptr;

	IGame* game;
	
	ShadowApplication::ShadowApplication() : window_(nullptr)
	{
		instance = this;

		game = _setupFunc();
	}


	ShadowApplication::~ShadowApplication()
	{
	}

	void ShadowApplication::Init()
	{
		moduleManager.PushModule(new Log());
		moduleManager.PushModule(new EventSystem::ShadowEventManager());
		moduleManager.PushModule(new SDLPlatform::SDLModule());
		moduleManager.PushModule(new Rendering::Renderer());
		moduleManager.PushModule(new DebugGui::ImGuiModule());
		moduleManager.PushModule(new InputSystem::ShadowActionSystem());
		//moduleManager.PushModule(new Debug::DebugModule());
		moduleManager.PushModule(new EntitySystem::EntitySystem());

		moduleManager.PushModule(new Assets::AssetManager());

		game->Init();
		
		moduleManager.Init();

		

	}

	void ShadowApplication::Start()
	{
		//ShadowWorld* w = AssetManager::GetAsset<ShadowWorld>("Resources/Worlds/Default/overworld.txt");
		//w->SetActiveMap("default");
		//w->Update(ShadowMath::Vector2float(0, 0));
		//ShadowMapRenderer::RenderMap(*map);

		auto renderer = moduleManager.GetModuleByType<ShadowEngine::Rendering::Renderer>();

		auto scenemg = moduleManager.GetModuleByType<EntitySystem::EntitySystem>();
		scenemg->LoadScene(new TestScene());

		//TestRenderer test;

		while (running)
		{
			Time::UpdateTime();

			renderer->BeginScene(scenemg->GetActiveScene()->mainCamera);

			EventSystem::ShadowEventManager::PollEvents();
			EventSystem::ShadowEventManager::ProcessEvents();

			moduleManager.Update();

			//test.Update();

			moduleManager.Render();

			moduleManager.LateRender();

			renderer->EndScene();

			//SDL_GL_SwapWindow(window_->winPtr);

			moduleManager.AfterFrameEnd();
		}
	}
}
