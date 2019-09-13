#pragma once
#include "ShadowInput/InputBinding.h"

namespace ShadowEngine::InputSystem
{
	
	class InputMapBinding
		: public InputBinding<bool>
	{
	public:
		InputMapBinding(const char* map);
		~InputMapBinding();
	};
}
