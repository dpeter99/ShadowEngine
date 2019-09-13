#include "shpch.h"

#include "SDLEventSource.h"
#include <SDL2/SDL.h>
#include "ShadowEvents/ShadowEventManager.h"
#include "ShadowEvents/Events/KeyEvents.h"
#include "ShadowEvents/Events/MouseEvents.h"
#include "ShadowEvents/Events/ApplicationEvent.h"

namespace ShadowEngine::SDLPlatform {

	void SDLEventSource::PollEvents() const
	{
		SDL_Event test_event;
		while (SDL_PollEvent(&test_event))
		{
			EventSystem::ShadowEvent* event = nullptr;
			switch (test_event.type)
			{
			case SDL_KEYDOWN:
			{
				event = new EventSystem::Events::KeyPressedEvent(test_event.key.keysym.scancode, test_event.key.repeat, &test_event);
			}
			break;
			case SDL_KEYUP:
			{
				event = new EventSystem::Events::KeyReleasedEvent(test_event.key.keysym.scancode, &test_event);
			}
			break;
			case SDL_MOUSEMOTION:
			{
				event = new EventSystem::Events::MouseMovedEvent(test_event.motion.x, test_event.motion.y, &test_event);
			}
			break;
			case SDL_MOUSEBUTTONDOWN:
			{
				event = new EventSystem::Events::MouseButtonPressedEvent(test_event.button.button, &test_event);
			}
			break;
			case SDL_MOUSEBUTTONUP:
			{
				event = new EventSystem::Events::MouseButtonReleasedEvent(test_event.button.button, &test_event);
			}
			break;
			case SDL_TEXTINPUT:
			{
				event = new EventSystem::Events::KeyTypedEvent(test_event.text.text, &test_event);
			}
			break;
			case SDL_WINDOWEVENT_CLOSE:
			{
				event = new EventSystem::Events::WindowCloseEvent(&test_event);

			}
			break;
			case SDL_WINDOWEVENT_RESIZED:
			{
				event = new EventSystem::Events::WindowResizeEvent(test_event.window.data1, test_event.window.data2, &test_event);
			}
			break;
			default:
				event = new EventSystem::ShadowEvent(&test_event);
				break;
			}


			if (event != nullptr)
				EventSystem::ShadowEventManager::PushNewEvent(event);
		}
	}

	SDLEventSource::SDLEventSource()
	{
	}


	SDLEventSource::~SDLEventSource()
	{
	}
}