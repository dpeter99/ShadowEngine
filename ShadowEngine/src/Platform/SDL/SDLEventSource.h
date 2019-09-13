#pragma once
#include "ShadowEvents/IShadowEventSource.h"

namespace ShadowEngine::SDLPlatform {

	class SDLEventSource : public EventSystem::IShadowEventSource
	{
	public:

		void PollEvents() const override;

		SDLEventSource();
		~SDLEventSource();
	};
}