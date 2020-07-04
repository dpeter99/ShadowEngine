#include "shpch.h"

#include "ShadowWindow.h"

#include "Log.h"
#include "ShadowRenderer/GraphicsContext.h"


ShadowWindow::ShadowWindow(int W, int H) : Height(H), Width(W)
{
	// Create window
	this->winPtr = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W, H,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	SH_CORE_ASSERT(winPtr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());

	context = ShadowEngine::Rendering::GraphicsContext::Create(this);
	context->Init();
}

ShadowWindow::~ShadowWindow()
{
}
