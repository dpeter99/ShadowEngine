#pragma once
#include "ShadowInput/InputBinding.h"

class BindingAND :
	public ShadowInput::InputBinding<bool>
{
	InputBinding<bool>* aBinding;
	InputBinding<bool>* bBinding;
public:
	BindingAND(const InputBinding* _a, const InputBinding* _b);
	~BindingAND();
};
