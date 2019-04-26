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

		void Binding1D::ProcessEvent(const InputContext& event)
		{
			//Call both bindings in this composite binding
			//Check the values they returned

			//Call the first one
			BindingContext<float> bindingContextPos;
			pos->ProcessEvent(bindingContextPos);




		}

		Binding1D(InputBinding<bool>* _positive, InputBinding<bool>* _negative) : pos(_positive),
			neg(_negative)
		{
		}

		~Binding1D()
		{
		}
	};
}
