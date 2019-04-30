#include "shpch.h"

#include "SDLModule.h"
#include <SDL2/SDL.h>
#include <cstdio>
#include "glad/glad.h"
#include <string>
#include "ShadowApplication.h"


void SDLModule::Init()
{
	// Initialize video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		// Display error message
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		//return false;
	}

	//Use OpenGL 3.1 core
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// Create window
	window = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 800,
	                          SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		// Display error message
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		//return false;
	}

	ShadowApplication::Get().SetWindow(new ShadowWindow(window, 1000, 800));

	// Create OpenGL context
	glContext = SDL_GL_CreateContext(window);

	if (glContext == nullptr)
	{
		// Display error message
		printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
		//return false;
	}

	// INITIALIZE GLAD:
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		throw (std::string("Failed to initialize GLAD"));
	}
}

SDLModule::SDLModule()
{
}


SDLModule::~SDLModule()
{
}
