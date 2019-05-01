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
#include "ShadowInput/Bindings/KeyboardBinding.h"
#include "ShadowInput/Modifiers/ModifierHold.h"
#include "ShadowInput/Bindings/Binding1D.h"
#include "Debug.h"

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


	new ShadowInput::ShadowAction<bool>("Test_continuous",
		new ShadowInput::KeyboardBinding(SDL_SCANCODE_Q),
		true
		);

	new ShadowInput::ShadowAction<bool>("Test_base",
		new ShadowInput::KeyboardBinding(SDL_SCANCODE_W)
		);

	new ShadowInput::ShadowAction<bool>("Test2",
		(new ShadowInput::KeyboardBinding(SDL_SCANCODE_E))->AddModifier(new ShadowInput::ModifierHold(500.0f))
	);

	new ShadowInput::ShadowAction<float>("Test1D_float",
		new ShadowInput::Binding1D(
			new ShadowInput::KeyboardBinding(SDL_SCANCODE_A),
			new ShadowInput::KeyboardBinding(SDL_SCANCODE_S)
		));

	new ShadowInput::ShadowAction<float>("Test1D_float_continuous",
		new ShadowInput::Binding1D(
			new ShadowInput::KeyboardBinding(SDL_SCANCODE_D),
			new ShadowInput::KeyboardBinding(SDL_SCANCODE_F)
		),true);

	new ShadowInput::ShadowAction<float>("Test1D_float_hold",
		(new ShadowInput::Binding1D(
			new ShadowInput::KeyboardBinding(SDL_SCANCODE_G),
			new ShadowInput::KeyboardBinding(SDL_SCANCODE_H)
		))->AddModifier(new ShadowInput::ModifierHold(500.0f)));

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

		//glClearColor(1, 0.3, 0.45, 0.92);
		glClearColor(0.09, 0.23, 0.90,1);
		glClear(GL_COLOR_BUFFER_BIT);

		ShadowEventManager::PollEvents();
		ShadowEventManager::ProcessEvents();

		moduleManager.Update();

		// Update window with OpenGL rendering
		SDL_GL_SwapWindow(window_->winPtr);
	}
}
