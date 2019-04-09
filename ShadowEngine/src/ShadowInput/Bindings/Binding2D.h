#pragma once
#include "ShadowInput/InputBinding.h"

namespace ShadowInput {

	class Binding2D
		: public InputBinding
	{
	public:
		Binding2D(const InputBinding* _xpositive, const InputBinding* _xnegative,
			const InputBinding* _ypositive, const InputBinding* _ynegative);
		~Binding2D();
	};

}
