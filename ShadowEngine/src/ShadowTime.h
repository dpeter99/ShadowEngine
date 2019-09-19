#pragma once
#include <SDL2/SDL_hints.h>
#include <SDL2/SDL.h>


class Time
{
	static Uint64 NOW;
	

public:
	static Uint64 LAST;

	static double deltaTime;
	static double deltaTime_ms;

	static void UpdateTime();
};
