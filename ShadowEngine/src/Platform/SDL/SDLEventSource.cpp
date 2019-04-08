#include "SDLEventSource.h"
#include <SDL2/SDL.h>
#include "ShadowEvents/ShadowEventManager.h"
#include "ShadowEvents/Events/KeyEvents.h"
#include "ShadowEvents/Events/MouseEvents.h"

void SDLEventSource::PollEvents() const
{
	SDL_Event test_event;
	while (SDL_PollEvent(&test_event)) {

		switch (test_event.type)
		{
		case SDL_KEYDOWN:
		{
			auto e_KeyPressedEvent = new KeyPressedEvent(test_event.key.keysym.scancode, test_event.key.repeat);
			ShadowEventManager::PushNewEvent(e_KeyPressedEvent);
		}
		break;
		case SDL_KEYUP:
		{
			auto e_KeyReleasedEvent = new KeyReleasedEvent(test_event.key.keysym.scancode);
			ShadowEventManager::PushNewEvent(e_KeyReleasedEvent);
		}
		break;
		case SDL_MOUSEMOTION:
		{
			auto e = new MouseMovedEvent(test_event.motion.x, test_event.motion.y);
			ShadowEventManager::PushNewEvent(e);
		}
		break;
		case SDL_MOUSEBUTTONDOWN:
		{
			auto e = new MouseButtonPressedEvent(test_event.button.button);
			ShadowEventManager::PushNewEvent(e);
		}
		break;
		case SDL_MOUSEBUTTONUP:
		{
			auto e = new MouseButtonReleasedEvent(test_event.button.button);
			ShadowEventManager::PushNewEvent(e);
		}
		break;
		case SDL_TEXTINPUT:
		{
			auto e = new KeyTypedEvent(test_event.text.text);
			ShadowEventManager::PushNewEvent(e);
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
