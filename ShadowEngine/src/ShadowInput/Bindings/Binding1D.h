#pragma once
#include "ShadowInput/InputBinding.h"

namespace ShadowInput
{
	class Binding1D
		: public InputBinding<float>
	{
	private:
		InputBinding<bool>* pos;
		InputBinding<bool>* neg;

	public:

		void ProcessEvent(const ShadowEvent& event) override;

		Binding1D(InputBinding<bool>* _xpositive, InputBinding<bool>* _xnegative);
		~Binding1D() override;
	};
}
