
/*

#include "ShadowInput/IShadowAction.h"
#include "ShadowInput/ShadowAction.h"
#include "ShadowInput/Bindings/KeyboardBinding.h"
#include <SDL2/SDL.h>
#include "ShadowInput/Modifiers/ModifierHold.h"

void RunTests()
{
	
	ShadowInput::ShadowActionSystem system;
	system.Init();


	new ShadowInput::ShadowAction<bool>("Test_continuous",
		new ShadowInput::KeyboardBinding(SDL_SCANCODE_A),
		true
		);

	new ShadowInput::ShadowAction<bool>("Test_base",
		new ShadowInput::KeyboardBinding(SDL_SCANCODE_Q)
		);

	new ShadowInput::ShadowAction<bool>("Test2",
		(new ShadowInput::KeyboardBinding(SDL_SCANCODE_D))->AddModifier(new ShadowInput::ModifierHold(500.0f))
		);

	//Add fake input and check the reaction
}
*/