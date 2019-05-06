#pragma once
#include "Debug/Inspector.h"
#include "ShadowInput/IInputBinding.h"
#include "ShadowInput/IShadowAction.h"

class InputActionInspector :
	public Inspector<ShadowInput::IShadowAction>

{
	SHObject_Base(InputActionInspector)


public:
	void Draw(ShadowInput::IShadowAction& obj) override
	{
		
	}
};
