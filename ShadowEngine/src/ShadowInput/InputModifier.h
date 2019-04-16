#pragma once
#include "InputContext.h"

class InputModifier
{

public:
	InputModifier();
	~InputModifier();

	virtual void ProcessInput(InputContext* ctx) = 0;
};

