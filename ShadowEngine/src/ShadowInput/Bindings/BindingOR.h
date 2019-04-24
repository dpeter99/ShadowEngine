#pragma once
#include "ShadowInput/InputBinding.h"

namespace ShadowInput {

	class BindingOR :
		public ShadowInput::InputBinding
	{
		InputBinding* aBinding;
		InputBinding* bBinding;
	public:
		BindingOR(const InputBinding* _a, const InputBinding* _b);
		~BindingOR();
	};

}