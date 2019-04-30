#pragma once
#include "ShadowInput/InputBinding.h"
#include "ShadowMap/ShadowWorld.h"
#include "ShadowMath/Vector2float.h"

namespace ShadowInput
{
	template <class I>
	class Binding2D
		: public InputBinding<ShadowMath::Vector2float>
	{
		InputBinding<I>* xpos_;
		InputBinding<I>* xneg_;

		InputBinding<I>* ypos_;
		InputBinding<I>* yneg_;

	public:
		Binding2D<I>(const InputBinding<I>* _xpositive, const InputBinding<I>* _xnegative,
					const InputBinding<I>* _ypositive, const InputBinding<I>* _ynegative);
		~Binding2D();
	};
}
