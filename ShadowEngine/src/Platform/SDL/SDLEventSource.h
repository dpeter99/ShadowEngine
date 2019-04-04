#pragma once
#include "ShadowEvents/IShadowEventSource.h"

class SDLEventSource : public IShadowEventSource
{
public:

	virtual void PollEvents() const override;

	SDLEventSource();
	~SDLEventSource();
};

