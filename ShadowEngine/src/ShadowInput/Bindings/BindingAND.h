#pragma once
#include "ShadowInput/InputBinding.h"

class BindingAND :
	public ShadowInput::InputBinding
{
public:
	BindingAND(const InputBinding* _a, const InputBinding* _b);
	~BindingAND();
};

