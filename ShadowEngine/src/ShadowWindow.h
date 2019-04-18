#pragma once
#include <SDL2/SDL.h>

class ShadowWindow
{
public:

	int Height;
	int Width;

	SDL_Window* winPtr;

	ShadowWindow(SDL_Window* ptr, int W, int H): Height(H), Width(W), winPtr(ptr)
	{
	};
	~ShadowWindow();
};
