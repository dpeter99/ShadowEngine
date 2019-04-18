#pragma once
#include "ShadowEvents/IShadowEventSource.h"

class SDLEventSource : public IShadowEventSource
{
public:

	void PollEvents() const override;

	SDLEventSource();
	~SDLEventSource();
};
