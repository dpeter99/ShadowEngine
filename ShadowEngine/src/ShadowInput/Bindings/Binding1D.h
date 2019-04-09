#pragma once
#include "ShadowInput/InputBinding.h"

namespace ShadowInput {

	class Binding1D
		: public InputBinding
	{
	public:
		Binding1D(InputBinding* _xpositive, InputBinding* _xnegative);
		~Binding1D();
	};

}
