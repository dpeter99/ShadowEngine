#include "KeyboardBinding.h"
#include "Utility.h"
#include "ShadowEvents/IShadowEventListener.h"
#include "KeyboardBinding.h"

namespace ShadowInput
{
	void KeyboardBinding::ProcessEvent(const ShadowEvent& e)
	{
		//"BIND" to the event
		ShadowEvent& ev = const_cast<ShadowEvent&>(e);

		KeyPressedEvent* _pressedEvent;
		if (is<KeyPressedEvent>(ev, &_pressedEvent))
		{
			if (this->SDLKey == _pressedEvent->GetKeyCode())
			{
				//We have a keystroke
				//Pass to the modifiers
				InputContext bindingContext;
				bindingContext.state_ = Started;
				for (auto modifier : modifiers_)
				{
					modifier->ProcessInput(&bindingContext);
				}
				action_->SetState(bindingContext.state_);
			}
		}

		KeyReleasedEvent* _releasedEvent;
		if (is<KeyReleasedEvent>(ev, &_releasedEvent))
		{
			if (this->SDLKey == _releasedEvent->GetKeyCode())
			{
				//We have a keystroke
				//Pass to the modifiers
				InputContext bindingContext;
				bindingContext.state_ = Ended;
				for (auto modifier : modifiers_)
				{
					modifier->ProcessInput(&bindingContext);
				}
				action_->SetState(bindingContext.state_);
			}
		}
	}

	KeyboardBinding::KeyboardBinding(const char* str)
	{
		keycode = new char;
		*keycode = *str;
	}

	KeyboardBinding::KeyboardBinding(const int sdl)
	{
		SDLKey = sdl;
	}

	KeyboardBinding::~KeyboardBinding()
	{
		delete keycode;
	}
}
