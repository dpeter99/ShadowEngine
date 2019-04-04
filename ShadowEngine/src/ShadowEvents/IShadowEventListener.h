#pragma once
class ShadowEvent;

class IShadowEventListener
{
public:

	virtual void OnEvent(ShadowEvent& e) = 0;

	IShadowEventListener() = default;
	~IShadowEventListener() = default;
};

