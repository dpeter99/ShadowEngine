#include "KeyboardBinding.h"
#include "Utility.h"
#include "ShadowEvents/IShadowEventListener.h"

namespace ShadowInput {

	void KeyboardBinding::ProcessEvent(InputContext<bool>* e)
	{
		ShadowEvent* ev = e->GetEvent();

		//"BIND" to the event
		KeyPressedEvent* _event;
		if(is<KeyPressedEvent>(ev,&_event))
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