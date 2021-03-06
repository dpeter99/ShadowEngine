#pragma once
#include <SDL.h>


#include "Core/Core.h"
#include "ShadowRenderer/GraphicsContext.h"

class ShadowWindow
{
public:

	int Height;
	int Width;

	SDL_Window* winPtr;

	ShadowEngine::Ref<ShadowEngine::Rendering::GraphicsContext> context;

	ShadowWindow(int W, int H);
	
	~ShadowWindow();
};
