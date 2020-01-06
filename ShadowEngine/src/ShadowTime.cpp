#include "shpch.h"

#include "Time.h"
#include <SDL_hints.h>
#include <SDL.h>
#include "ShadowTime.h"

Uint64 Time::NOW = SDL_GetPerformanceCounter();
Uint64 Time::LAST = 0;
double Time::deltaTime_ms = 0;
double Time::deltaTime = 0;

void Time::UpdateTime()
{
	/*
	NOW = SDL_GetPerformanceCounter();

	static Uint64 frequency = SDL_GetPerformanceFrequency();
	deltaTime_ms = LAST > 0 ? ((double)(NOW - LAST)*1000 / frequency) : (1.0f / 60.0f);
	deltaTime = deltaTime_ms * 0.001;
	LAST = NOW;
	*/
	//double m_time = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());
	
	//deltaTime = m_time > 0 ? m_time : (1.0 / 60.0);

	NOW = SDL_GetTicks();
	deltaTime_ms = LAST > 0 ? (NOW - LAST) *10 : (1.0f / 60.0f);
	deltaTime_ms = deltaTime_ms == 0 ? (1.0f / 60.0f) : deltaTime_ms;

	LAST = NOW;
	deltaTime = deltaTime_ms * 0.001;
}
