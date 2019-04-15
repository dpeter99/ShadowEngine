#pragma once
#include "ShadowInput/InputBinding.h"

namespace ShadowInput {

	class Binding1D
		: public InputBinding<float>
	{
	public:
		Binding1D(InputBinding<bool>* _xpositive, InputBinding<bool>* _xnegative);
		~Binding1D();
	};

}
