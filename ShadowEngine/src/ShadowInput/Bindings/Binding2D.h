#pragma once
#include "ShadowInput/InputBinding.h"

namespace ShadowInput
{
	class Binding2D
		: public InputBinding
	{
		InputBinding* xpos_;
		InputBinding* xneg_;

		InputBinding* ypos_;
		InputBinding* yneg_;

	public:
		Binding2D(const InputBinding* _xpositive, const InputBinding* _xnegative,
		          const InputBinding* _ypositive, const InputBinding* _ynegative);
		~Binding2D();
	};
}
