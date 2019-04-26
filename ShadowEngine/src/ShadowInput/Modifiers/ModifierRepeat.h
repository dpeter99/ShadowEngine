#pragma once
#include "ShadowInput/InputModifier.h"

namespace ShadowInput
{
	class ModifierRepeat
		: public InputModifier
	{
	public:

		void ProcessInput(BindingContext* ctx) override;

		ModifierRepeat(int count);
		~ModifierRepeat();
	};
}
