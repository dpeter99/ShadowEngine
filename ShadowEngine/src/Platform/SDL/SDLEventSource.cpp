#include "SDLEventSource.h"
#include <SDL2/SDL.h>
#include "ShadowEvents/ShadowEventManager.h"
#include "ShadowEvents/Events/KeyEvents.h"

void SDLEventSource::PollEvents() const
{
	SDL_Event test_event;
	while (SDL_PollEvent(&test_event)) {

		switch (test_event.type)
		{
		case SDL_KEYDOWN: {
			auto e_KeyPressedEvent = new KeyPressedEvent(test_event.key.keysym.sym, test_event.key.repeat);
			ShadowEventManager::PushNewEvent(e_KeyPressedEvent);
		}
			break;
		case SDL_KEYUP: {
			auto e_KeyReleasedEvent = new KeyReleasedEvent(test_event.key.keysym.sym);
			ShadowEventManager::PushNewEvent(e_KeyReleasedEvent);
		}
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
