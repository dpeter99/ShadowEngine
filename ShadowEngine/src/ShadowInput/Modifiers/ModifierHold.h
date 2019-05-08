#pragma once
#include "ShadowInput/InputModifier.h"

namespace ShadowInput
{
	class ModifierHold :
		public InputModifier
	{
		SHObject_Base(ModifierHold)

		double wait_;

		double deltaTime;

	public:

		float GetWaitTime();

		float GetDeltaTime();

		void ProcessInput(ModifierContext& ctx) override;

		ModifierHold(const double time, bool cont = false) : InputModifier(), wait_(time), deltaTime(0)
		{
		};
		~ModifierHold();

		bool RequieresContinous() override;
	};
}
