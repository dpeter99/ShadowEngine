#pragma once
#include "ShadowInput/InputBinding.h"

namespace ShadowInput {

	class Binding2D
		: public InputBinding<float>
	{

		InputBinding<bool>* xpos_;
		InputBinding<bool>* xneg_;

		InputBinding<bool>* ypos_;
		InputBinding<bool>* yneg_;

	public:
		Binding2D(const InputBinding<bool>* _xpositive, const InputBinding<bool>* _xnegative,
			const InputBinding<bool>* _ypositive, const InputBinding<bool>* _ynegative);
		~Binding2D();
	};

}
