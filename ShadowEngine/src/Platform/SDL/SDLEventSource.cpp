#include "SDLEventSource.h"
#include <SDL2/SDL.h>
#include "ShadowEvents/ShadowEventManager.h"

void SDLEventSource::PollEvents()
{
	SDL_Event test_event;
	while (SDL_PollEvent(&test_event)) {

		switch (test_event.type)
		{
		case SDL_KEYDOWN:

			ShadowEventManager::PushNewEvent();
			break;
		}
	}
}

SDLEventSource::SDLEventSource()
{
}


SDLEventSource::~SDLEventSource()
{
}
