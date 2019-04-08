#pragma once
#include "ShadowInput/InputEventSource.h"

class KeyboardInput :
	public InputEventSource
{

	char* keycode;

public:

	void ProcessEvent(ShadowEvent& event_) override;

	KeyboardInput();
	~KeyboardInput();
};

