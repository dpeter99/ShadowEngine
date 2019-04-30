#pragma once
#include "ShadowInput/InputBinding.h"

namespace ShadowInput {

	template<class I>
	class BindingOR :
		public InputBinding<I>
	{
		InputBinding<I>* aBinding;
		InputBinding<I>* bBinding;
	public:
		BindingOR(const InputBinding<I>* _a, const InputBinding<I>* _b);
		~BindingOR();
	};

}