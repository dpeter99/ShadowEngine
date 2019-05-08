#pragma once
#include "BindingContext.h"
#include "ShadowInput/ModifierContext.h"
#include "SHObject.h"

namespace ShadowInput {

	class InputModifier : public SHObject
	{
		SHObject_Base(InputModifier)

	public:
		virtual void ProcessInput(ModifierContext& ctx) = 0;
		virtual bool RequieresContinous() = 0;

		InputModifier();
		~InputModifier();
	};

}
