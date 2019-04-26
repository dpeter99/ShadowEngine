#include "KeyboardBinding.h"
#include "Utility.h"
#include "ShadowEvents/IShadowEventListener.h"
#include "KeyboardBinding.h"

namespace ShadowInput
{
	int KeyboardBinding::GetKeycode()
	{
		return SDLKey;
	}

	void KeyboardBinding::ProcessEvent(const ShadowEvent& e)
	{
		//"BIND" to the event
		ShadowEvent& ev = const_cast<ShadowEvent&>(e);

		InputContext bindingContext;
		bindingContext.event_ = &e;

		bool processed = false;

		KeyPressedEvent* _pressedEvent;
		if (is<KeyPressedEvent>(ev, &_pressedEvent))
		{
			
			if (this->SDLKey == _pressedEvent->GetKeyCode())
			{
				//We have a keystroke
				processed = true;
				bindingContext.bindingState_ = true;
				if(action_->IsContinuous())
				{
						natureState = ActionState::Performed;
				}
				else
				{
					if(_pressedEvent->GetRepeatCount() == 0)
					natureState = ActionState::Performed;
					else
						natureState = ActionState::Idle;
				}
			}
		}

		KeyReleasedEvent* _releasedEvent;
		if (is<KeyReleasedEvent>(ev, &_releasedEvent))
		{
			
			if (this->SDLKey == _releasedEvent->GetKeyCode())
			{
				
				//We have a keystroke
				processed = true;
				bindingContext.bindingState_ = false;
				
					natureState = ActionState::Idle;
				
			}
		}

		if(processed)
		ProcessContext(&bindingContext);
	}

	void KeyboardBinding::DefaultBehaviour(InputContext* ctx)
	{
		ctx->outstate_ = natureState;
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
