#pragma once
#include "InputContext.h"

class InputModifier
{
protected:

public:
	virtual void ProcessInput(InputContext* ctx) = 0;

	InputModifier();
	~InputModifier();
};
