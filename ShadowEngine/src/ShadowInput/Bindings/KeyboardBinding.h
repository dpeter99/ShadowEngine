#pragma once
#include "ShadowInput/InputBinding.h"
#include "ShadowInput/InputContext.h"

namespace ShadowInput
{
	class KeyboardBinding :
		public InputBinding<bool>
	{
		char* keycode;
		int SDLKey;

	public:

		void ProcessEvent(const ShadowEvent& event_) override;

		KeyboardBinding(const char* str);
		KeyboardBinding(const int sld);
		~KeyboardBinding() override;
	};
}
