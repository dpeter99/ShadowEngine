#pragma once
#include "ShadowInput/InputBinding.h"

class BindingOR :
	public ShadowInput::InputBinding
{
public:
	BindingOR(const InputBinding* _a, const InputBinding* _b);
	~BindingOR();
};

