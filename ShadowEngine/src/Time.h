#pragma once
#include <SDL2/SDL_hints.h>
#include <SDL2/SDL.h>


class Time
{
	static Uint64 NOW;
	static Uint64 LAST;

public:
	static double deltaTime;

	static void UpdateTime();
};
