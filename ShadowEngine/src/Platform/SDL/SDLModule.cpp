#include "shpch.h"

#include "SDLModule.h"
#include <SDL.h>
#include <cstdio>
#include "glad/glad.h"
#include <string>
#include "Core/ShadowApplication.h"

namespace ShadowEngine::SDLPlatform {

	SDLModule* SDLModule::instance = nullptr;

	void SDLModule::Init()
	{
		instance = this;

		// Initialize video subsystem
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			// Display error message
			SH_CORE_ERROR("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
			//printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
			//return false;
		}

		ShadowApplication::Get().SetWindow(new ShadowWindow(1000, 700));
	}

	SDLModule::SDLModule()
	{
	}


	SDLModule::~SDLModule()
	{
	}
}