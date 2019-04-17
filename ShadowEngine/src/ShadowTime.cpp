#include "Time.h"
#include <SDL2/SDL_hints.h>
#include <SDL2/SDL.h>
#include "ShadowTime.h"

Uint64 Time::NOW = SDL_GetPerformanceCounter();
Uint64 Time::LAST = 0;
double Time::deltaTime = 0;

void Time::UpdateTime()
{
	LAST = NOW;
	NOW = SDL_GetPerformanceCounter();

	double m_time = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());

	deltaTime = m_time > 0?m_time:(1.0/60.0);
}
