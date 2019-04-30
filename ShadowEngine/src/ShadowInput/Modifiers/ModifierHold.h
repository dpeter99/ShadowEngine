#pragma once
#include "ShadowInput/InputModifier.h"

namespace ShadowInput
{
	class ModifierHold :
		public InputModifier
	{
		float wait_;

		float deltaTime;

	public:

		float GetWaitTime();

		float GetDeltaTime();

		void ProcessInput(ModifierContext& ctx) override;

		ModifierHold(const float time, bool cont = false) : InputModifier(), wait_(time), deltaTime(0)
		{
		};
		~ModifierHold();
	};
}
