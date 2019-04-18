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
#include "ShadowInput/ShadowActionSystem.h"
#include "ShadowInput/Bindings/KeyboardBinding.h"
#include "ShadowInput/Modifiers/ModifierHold.h"


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
	moduleManager.PushModule(new ShadowInput::ShadowActionSystem());
	moduleManager.PushModule(new Debug());


	moduleManager.Init();


	new ShadowInput::ShadowAction<bool>("Test",
		new ShadowInput::KeyboardBinding(SDL_SCANCODE_A),
		true
		);

	new ShadowInput::ShadowAction<bool>("Test2",
		(new ShadowInput::KeyboardBinding(SDL_SCANCODE_D))->AddModifier(new ShadowInput::ModifierHold(3.0f))
		);

}

void ShadowApplication::Start()
{
	//ShadowWorld* w = AssetManager::GetAsset<ShadowWorld>("Resources/Worlds/Default/overworld.txt");
	//w->SetActiveMap("default");
	//w->Update(ShadowMath::Vector2float(0, 0));
	//ShadowMapRenderer::RenderMap(*map);

	while (running)
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
