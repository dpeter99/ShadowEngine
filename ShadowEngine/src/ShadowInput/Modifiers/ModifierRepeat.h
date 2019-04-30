#pragma once
#include "ShadowInput/InputModifier.h"

namespace ShadowInput
{
	class ModifierRepeat
		: public InputModifier
	{
	public:

		void ProcessInput(ModifierContext& ctx) override;

		ModifierRepeat(int count);
		~ModifierRepeat();
	};
}
