#include "SDLModule.h"
#include <SDL2/SDL.h>
#include <cstdio>
#include "glad/glad.h"
#include <string>


void SDLModule::Init()
{
	// Initialize video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		// Display error message
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		//return false;
	}

	//Use OpenGL 3.1 core
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// Create window
	window = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (window == NULL) {
		// Display error message
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		//return false;
	}

	// Create OpenGL context
	glContext = SDL_GL_CreateContext(window);

	if (glContext == NULL) {
		// Display error message
		printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
		//return false;
	}

	// INITIALIZE GLAD:
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		throw (std::string("Failed to initialize GLAD"));
	}
}

SDLModule::SDLModule()
{
}


SDLModule::~SDLModule()
{
}
