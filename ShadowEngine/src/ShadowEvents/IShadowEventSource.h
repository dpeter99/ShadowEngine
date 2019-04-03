#pragma once
class IShadowEventSource
{
public:

	virtual void PollEvents();

	IShadowEventSource();
	virtual ~IShadowEventSource();
};

