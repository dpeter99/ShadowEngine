#include "Utility.h"
#include "ShadowEvents/IShadowEventListener.h"
#include "KeyboardBinding.h"

namespace ShadowInput {

	void KeyboardBinding::ProcessEvent(ShadowEvent& e)
	{
		EVENT_BIND(e, KeyPressedEvent,
			{
				if (this->keycode[0] == _event->GetKeyCode())
				{

				}
			})
	}

}
