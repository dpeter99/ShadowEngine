#pragma once
#include "ShadowEvents/IShadowEventSource.h"

class SDLEventSource : public IShadowEventSource
{
public:

	virtual void PollEvents() override;

	SDLEventSource();
	~SDLEventSource();
};

