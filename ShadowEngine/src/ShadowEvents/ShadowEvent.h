#pragma once
#include  "shpch.h"
#include "Core/Core.h"
#include "Core/SHObject.h"
#include <SDL2/SDL.h>

namespace ShadowEngine::EventSystem {

	class ShadowEvent : public ShadowEngine::SHObject
	{
		SHObject_Base(ShadowEvent)

	private:
		SDL_Event* sdl_event;

	public:
		bool Handled = false;

		virtual std::string ToString() const { return GetType(); }

		SDL_Event* GetSDLEvnet() { return sdl_event; };

		ShadowEvent(SDL_Event* ev)
		{
			sdl_event = ev;
		};

		virtual ~ShadowEvent(){}
	};

	inline std::ostream& operator<<(std::ostream& os, const class ShadowEvent& e)
	{
		return os << e.ToString();
	}

}
