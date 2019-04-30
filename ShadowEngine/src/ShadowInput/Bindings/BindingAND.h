#pragma once
#include "ShadowInput/InputBinding.h"

namespace ShadowInput {

	template <class I>
	class BindingAND :
		public InputBinding<I>
	{
		InputBinding<I>* aBinding;
		InputBinding<I>* bBinding;
	public:
		BindingAND<I>(const InputBinding<I>* _a, const InputBinding<I>* _b);
		~BindingAND();
	};

}