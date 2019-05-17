#pragma once
#include "ShadowEvents/IShadowEventSource.h"

class SDLEventSource : public ShadowEventSystem::IShadowEventSource
{
public:

	void PollEvents() const override;

	SDLEventSource();
	~SDLEventSource();
};
