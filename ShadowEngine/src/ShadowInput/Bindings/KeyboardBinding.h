#pragma once
#include "ShadowInput/InputBinding.h"
#include "ShadowInput/InputContext.h"

namespace ShadowInput
{
	class KeyboardBinding :
		public InputBinding//<bool>
	{
		char* keycode;
		int SDLKey;

		ActionState natureState;

	public:

		int GetKeycode();

		void ProcessEvent(const ShadowEvent& event_) override;

		void DefaultBehaviour(InputContext* ctx) override;

		KeyboardBinding(const char* str);
		KeyboardBinding(const int sld);
		~KeyboardBinding() override;
	};
}
