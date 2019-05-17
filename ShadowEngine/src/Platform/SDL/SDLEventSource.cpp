#include "shpch.h"

#include "SDLEventSource.h"
#include <SDL2/SDL.h>
#include "ShadowEvents/ShadowEventManager.h"
#include "ShadowEvents/Events/KeyEvents.h"
#include "ShadowEvents/Events/MouseEvents.h"
#include "ShadowEvents/Events/ApplicationEvent.h"

void SDLEventSource::PollEvents() const
{
	SDL_Event test_event;
	while (SDL_PollEvent(&test_event))
	{
		ShadowEventSystem::ShadowEvent* event = nullptr;
		switch (test_event.type)
		{
		case SDL_KEYDOWN:
		{
			event = new ShadowEventSystem::KeyPressedEvent(test_event.key.keysym.scancode, test_event.key.repeat, &test_event);
		}
		break;
		case SDL_KEYUP:
		{
			event = new ShadowEventSystem::KeyReleasedEvent(test_event.key.keysym.scancode, &test_event);
		}
		break;
		case SDL_MOUSEMOTION:
		{
			event = new ShadowEventSystem::MouseMovedEvent(test_event.motion.x, test_event.motion.y, &test_event);
		}
		break;
		case SDL_MOUSEBUTTONDOWN:
		{
			event = new ShadowEventSystem::MouseButtonPressedEvent(test_event.button.button, &test_event);
		}
		break;
		case SDL_MOUSEBUTTONUP:
		{
			event = new ShadowEventSystem::MouseButtonReleasedEvent(test_event.button.button, &test_event);
		}
		break;
		case SDL_TEXTINPUT:
		{
			event = new ShadowEventSystem::KeyTypedEvent(test_event.text.text, &test_event);
		}
		break;
		case SDL_WINDOWEVENT_CLOSE:
		{
			event = new ShadowEventSystem::WindowCloseEvent(&test_event);
			
		}
		break;
		case SDL_WINDOWEVENT_RESIZED:
		{
			event = new ShadowEventSystem::WindowResizeEvent(test_event.window.data1, test_event.window.data2, &test_event);
		}
		break;
		default:
			event = new ShadowEventSystem::ShadowEvent(&test_event);
			break;
		}


		if(event != nullptr)
		ShadowEventSystem::ShadowEventManager::PushNewEvent(event);
	}
}

SDLEventSource::SDLEventSource()
{
}


SDLEventSource::~SDLEventSource()
{
}
