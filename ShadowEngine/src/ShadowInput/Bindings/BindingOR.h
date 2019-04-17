#pragma once
#include "ShadowInput/InputBinding.h"

class BindingOR :
	public ShadowInput::InputBinding<bool>
{
	InputBinding<bool>* aBinding;
	InputBinding<bool>* bBinding;
public:
	BindingOR(const InputBinding* _a, const InputBinding* _b);
	~BindingOR();
};

