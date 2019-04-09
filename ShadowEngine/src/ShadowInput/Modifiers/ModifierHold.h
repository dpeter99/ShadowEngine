#pragma once
#include "ShadowInput/InputModifier.h"

namespace ShadowInput {

	class ModifierHold :
		public InputModifier
	{

		float wait_;

	public:

		void ProcessInput() override;

		ModifierHold(const float time, bool cont = false) : InputModifier(), wait_(time) {};
		~ModifierHold();
	};

}