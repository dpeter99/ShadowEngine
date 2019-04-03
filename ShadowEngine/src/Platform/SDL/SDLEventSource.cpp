#include "SDLEventSource.h"
#include <SDL2/SDL.h>
#include "ShadowEvents/ShadowEventManager.h"
#include "ShadowEvents/Events/KeyEvents.h"

void SDLEventSource::PollEvents()
{
	SDL_Event test_event;
	while (SDL_PollEvent(&test_event)) {

		switch (test_event.type)
		{
		case SDL_KEYDOWN:
			KeyPressedEvent* e = new KeyPressedEvent(test_event.key.keysym.sym,test_event.key.repeat);
			ShadowEventManager::PushNewEvent(e);
			break;
		case SDL_KEYUP:
			KeyReleasedEvent* e = new KeyReleasedEvent(test_event.key.keysym.sym);
			ShadowEventManager::PushNewEvent(e);
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
