#pragma once
class IShadowEventSource
{
public:

	virtual void PollEvents() const = 0;

	IShadowEventSource();
	virtual ~IShadowEventSource();
};

