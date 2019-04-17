#include "KeyboardBinding.h"
#include "Utility.h"
#include "ShadowEvents/IShadowEventListener.h"
#include "KeyboardBinding.h"

namespace ShadowInput {

	void KeyboardBinding::ProcessEvent(const ShadowEvent& e)
	{
		//"BIND" to the event
		ShadowEvent& ev = const_cast<ShadowEvent&>(e);
		KeyPressedEvent* _event;
		if(is<KeyPressedEvent>(ev,&_event))
		{
			if (this->keycode[0] == _event->GetKeyCode())
			{
				//We have a keystroke
				//Pass to the modifiers
				InputContext bindingContext;
				bindingContext.state_ = ActionState::Started;
				for (auto modifier : modifiers_)
				{
					modifier->ProcessInput(&bindingContext);
				}
			}
		}
	}

	KeyboardBinding::KeyboardBinding(const char* str)
	{
		keycode = new char;
		*keycode = *str;
	}
	
	KeyboardBinding::~KeyboardBinding()
	{
		delete keycode;
	}
}
