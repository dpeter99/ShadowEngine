#pragma once
#include "ShadowInput/InputBinding.h"

namespace ShadowInput
{
	template <class T>
	class InputMapBinding
		: public InputBinding<T>
	{
	public:
		InputMapBinding(const char* map);
		~InputMapBinding();
	};
}
