#include "shpch.h"

#include "ShadowApplication.h"
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
#include "ShadowScene/SceneManager.h"
#include "ShadowScene/TestScene.h"


ShadowEngine::ShadowApplication* ShadowEngine::ShadowApplication::instance = nullptr;

ShadowEngine::ShadowApplication::ShadowApplication()
{
	instance = this;
}


ShadowEngine::ShadowApplication::~ShadowApplication()
{
}

void ShadowEngine::ShadowApplication::Init()
{
	moduleManager.PushModule(new ShadowEngine::Log());
	moduleManager.PushModule(new ShadowEventSystem::ShadowEventManager());
	moduleManager.PushModule(new SDLModule::SDLModule());
	moduleManager.PushModule(new ShadowRenderer::Renderer());
	moduleManager.PushModule(new ImGuiModule());
	moduleManager.PushModule(new ShadowInput::ShadowActionSystem());
	moduleManager.PushModule(new Debug());
	moduleManager.PushModule(new ShadowScene::SceneManager());

	moduleManager.Init();

	
	
}

void ShadowEngine::ShadowApplication::Start()
{
	//ShadowWorld* w = AssetManager::GetAsset<ShadowWorld>("Resources/Worlds/Default/overworld.txt");
	//w->SetActiveMap("default");
	//w->Update(ShadowMath::Vector2float(0, 0));
	//ShadowMapRenderer::RenderMap(*map);

	auto renderer = moduleManager.GetModuleByType<ShadowRenderer::Renderer>();

	auto scenemg = moduleManager.GetModuleByType<ShadowScene::SceneManager>();
	scenemg->LoadScene(new TestScene());
	

	TestRenderer test;
	
	while (running)
	{
		Time::UpdateTime();

		renderer->BeginScene(*scenemg->GetActiveScene()->mainCamera);

		ShadowEventSystem::ShadowEventManager::PollEvents();
		ShadowEventSystem::ShadowEventManager::ProcessEvents();

		moduleManager.Update();

		test.Update();

		moduleManager.Render();

		moduleManager.LateRender();
		
		ShadowRenderer::Renderer::EndScene();

		SDL_GL_SwapWindow(window_->winPtr);
	}
}
