#pragma once
#include "ShadowInput/BindingContext.h"

class ModifierContext
{
public:

	const ShadowEvent* event_;

	bool bindingState_;
	ActionState outstate_;

	ModifierContext();
	~ModifierContext();
};

