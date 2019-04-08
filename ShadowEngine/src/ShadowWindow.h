#pragma once
#include <SDL2/SDL.h>

class ShadowWindow
{
public:

	int Height;
	int Width;

	SDL_Window* winPtr;

	ShadowWindow(SDL_Window* ptr,int W,int H):winPtr(ptr),Height(H),Width(W){};
	~ShadowWindow();
};

