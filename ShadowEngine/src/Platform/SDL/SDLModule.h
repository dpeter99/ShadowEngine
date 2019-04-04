#pragma once
#include "ShadowModules/ShadowModule.h"
#include <SDL2/SDL.h>

class SDLModule : public ShadowModule
{
	SDL_Window* window;
	SDL_GLContext glContext;
	//SDL_Event sdlEvent;

public:

	virtual void Init() override;

	SDLModule();
	~SDLModule();
};

