#pragma once
#include "Debug/Inspector.h"
#include "ShadowInput/IInputBinding.h"
#include "ShadowInput/IShadowAction.h"
#include "ShadowInput/Bindings/KeyboardBinding.h"

class KeyboardBindingInspector :
	public Inspector<ShadowInput::KeyboardBinding>

{
	SHObject_Base(KeyboardBindingInspector)


public:
	void Draw(ShadowInput::KeyboardBinding& obj) override
	{
		
	}
};
