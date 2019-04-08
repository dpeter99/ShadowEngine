#pragma once
#include "ShadowInput/InputModifier.h"

class ModifierHold :
	public InputModifier
{

	float wait_;	

public:

	void ProcessInput() override;

	ModifierHold(const float _wait) : InputModifier(), wait_(_wait) {};
	~ModifierHold();
};

