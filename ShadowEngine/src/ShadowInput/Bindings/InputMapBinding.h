#pragma once
#include "ShadowInput/InputBinding.h"

namespace ShadowInput
{
	
	class InputMapBinding
		: public InputBinding<bool>
	{
	public:
		InputMapBinding(const char* map);
		~InputMapBinding();
	};
}
