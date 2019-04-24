#pragma once
#include "ShadowInput/InputBinding.h"

namespace ShadowInput
{
	class Binding1D
		: public InputBinding
	{
	private:
		InputBinding* pos;
		InputBinding* neg;

	public:

		void ProcessEvent(const ShadowEvent& event) override;

		Binding1D(InputBinding* _xpositive, InputBinding* _xnegative);
		~Binding1D() override;
	};
}
