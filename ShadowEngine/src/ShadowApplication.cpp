#include "ShadowApplication.h"
#include "ShadowModules/ShadowModuleManager.h"
#include "ShadowMap/ShadowWorld.h"
#include "ShadowAsset/AssetManager.h"
#include "ShadowMap/ShadowMapRenderer.h"
#include "ShadowEvents/ShadowEventManager.h"
#include "Platform/SDL/SDLModule.h"
#include "Debug.h"
#include "ImGui/ImGuiModule.h"
#include "glad/glad.h"
#include "ShadowMath/Vector2float.h"
#include "ShadowTime.h"


ShadowApplication* ShadowApplication::instance = nullptr;

ShadowApplication::ShadowApplication()
{
	instance = this;
}


ShadowApplication::~ShadowApplication()
{
}

void ShadowApplication::Init()
{
	moduleManager.PushModule(new ShadowEventManager());
	moduleManager.PushModule(new SDLModule());
	moduleManager.PushModule(new ImGuiModule());
	moduleManager.PushModule(new Debug());
	

	moduleManager.Init();
}

void ShadowApplication::Start()
{
	ShadowWorld* w = AssetManager::GetAsset<ShadowWorld>("Resources/Worlds/Default/overworld.txt");
	w->SetActiveMap("default");
	w->Update(ShadowMath::Vector2float(0, 0));
	//ShadowMapRenderer::RenderMap(*map);

	while(running)
	{
		Time::UpdateTime();

		glClearColor(1, 0, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		ShadowEventManager::PollEvents();
		ShadowEventManager::ProcessEvents();

		moduleManager.Update();

		// Update window with OpenGL rendering
		SDL_GL_SwapWindow(window_->winPtr);
	}
}
