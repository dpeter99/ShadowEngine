#pragma once
#include "ShadowInput/InputBinding.h"

class KeyboardInput :
	public InputBinding
{

	char* keycode;

public:

	void ProcessEvent(ShadowEvent& event_) override;

	KeyboardInput();
	~KeyboardInput();
};

