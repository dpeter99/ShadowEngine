#pragma once
#include "ShadowInput/InputBinding.h"
#include "ShadowInput/InputContext.h"

namespace ShadowInput {

	class KeyboardBinding :
		public InputBinding<bool>
	{

		char* keycode;

	public:

		void ProcessEvent(InputContext<bool>* event_);

		KeyboardBinding(const char* str);
		~KeyboardBinding();
	};
}
