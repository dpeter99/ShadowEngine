#pragma once
#include "ShadowInput/InputBinding.h"

namespace ShadowInput {

	class BindingAND :
		public InputBinding
	{
		InputBinding* aBinding;
		InputBinding* bBinding;
	public:
		BindingAND(const InputBinding* _a, const InputBinding* _b);
		~BindingAND();
	};

}