#pragma once
#include "BindingContext.h"
#include "ShadowInput/ModifierContext.h"

class InputModifier
{
protected:

public:
	virtual void ProcessInput(ModifierContext& ctx) = 0;

	InputModifier();
	~InputModifier();
};
