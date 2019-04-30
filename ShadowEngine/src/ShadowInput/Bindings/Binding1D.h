#pragma once
#include "ShadowInput/InputBinding.h"

namespace ShadowInput
{
	template <class I>
	class Binding1D
		: public InputBinding<float>
	{
	private:
		InputBinding<I>* pos;
		InputBinding<I>* neg;

	public:

		void ProcessEvent(BindingContext<float>& event) override
		{
			//Call both bindings in this composite binding
			//Check the values they returned

			//Call the first one
			BindingContext<I> bindingContextPos;
			pos->ProcessEvent(bindingContextPos);




		}

		void DefaultBehaviour(ModifierContext& ctx) override
		{
			
		}

		Binding1D<I>(InputBinding<I>* _positive, InputBinding<I>* _negative) : pos(_positive),
			neg(_negative)
		{
		}

		~Binding1D()
		{
		}
	};
}
