#pragma once
#include "ShadowEvents/IShadowEventSource.h"

namespace SDLModule {

	class SDLEventSource : public ShadowEventSystem::IShadowEventSource
	{
	public:

		void PollEvents() const override;

		SDLEventSource();
		~SDLEventSource();
	};
}