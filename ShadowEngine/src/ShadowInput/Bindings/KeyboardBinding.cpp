#include "KeyboardBinding.h"
#include "Utility.h"
#include "ShadowEvents/IShadowEventListener.h"
#include "KeyboardBinding.h"

namespace ShadowInput {

	void KeyboardBinding::ProcessEvent(const ShadowEvent& e)
	{
		//ShadowEvent& ev = e;

		//"BIND" to the event
		KeyPressedEvent* _event;
		if(is<KeyPressedEvent>(e,&_event))
		{
			if (this->keycode[0] == _event->GetKeyCode())
			{
				//We have a keystroke
				e->state_ = ActionState::Started;
				//Pass to the modifiers
				for (auto modifier : modifiers_)
				{
					modifier->ProcessInput(e);
				}
			}
		}
	}

	KeyboardBinding::KeyboardInput()
	{
	}


	KeyboardBinding::~KeyboardInput()
	{
	}

}