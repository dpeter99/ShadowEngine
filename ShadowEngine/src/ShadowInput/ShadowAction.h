#pragma once
#include "InputBinding.h"

namespace ShadowInput {

	class ShadowAction
	{

		bool active;
		//TODO: Delegates to activate
		//TODO: link to the activation tree
		//InputBinding& source_;

	public:
		ShadowAction(std::string a, ShadowInput::InputBinding& b, bool continous = false);
		~ShadowAction();
	};

}
