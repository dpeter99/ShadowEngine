#pragma once
#include <SDL_hints.h>
#include <SDL.h>


class Time
{
	static Uint64 NOW;
	

public:
	static Uint64 LAST;

	static double deltaTime;
	static double deltaTime_ms;

	static void UpdateTime();
};
