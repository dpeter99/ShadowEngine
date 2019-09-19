#pragma once
#include "ShadowInput/InputModifier.h"

namespace ShadowEngine::InputSystem
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
