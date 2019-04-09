#pragma once
#include "ShadowInput/InputBinding.h"

namespace ShadowInput {

	class KeyboardBinding :
		public ShadowInput::InputBinding
	{

		char* keycode;

	public:

		void ProcessEvent(ShadowEvent& event_) override;

		KeyboardBinding();
		~KeyboardBinding();
	};

}