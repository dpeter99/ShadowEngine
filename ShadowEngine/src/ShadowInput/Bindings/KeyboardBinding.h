#pragma once
#include "ShadowInput/InputBinding.h"

namespace ShadowInput {

	class KeyboardBinding :
		public InputBinding
	{

		char* keycode;

	public:

		void ProcessEvent(ShadowEvent& event_) override;

		KeyboardBinding(const char* str);
		~KeyboardBinding();
	};

}