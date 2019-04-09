#pragma once
#include "ShadowInput/InputModifier.h"

namespace ShadowInput {

	class InputMapBinding
		: public InputModifier
	{
	public:
		InputMapBinding(const char* map);
		~InputMapBinding();
	};

}

