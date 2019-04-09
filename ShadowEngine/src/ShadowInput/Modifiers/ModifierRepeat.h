#pragma once
#include "ShadowInput/InputModifier.h"

namespace ShadowInput {

	class ModifierRepeat
		: public InputModifier
	{
	public:
		ModifierRepeat(int count);
		~ModifierRepeat();
	};

}
