#pragma once
#include "ShadowInput/InputBinding.h"
#include "ShadowInput/BindingContext.h"
#include "ShadowEvents/Events/KeyEvents.h"
#include "Utility.h"
#include "ShadowInput/ModifierContext.h"

//class ModifierContext;

namespace ShadowInput
{
	class KeyboardBinding :
		public InputBinding<bool>
	{
		char* keycode;
		int SDLKey;

		ActionState natureState;

	public:

		int GetKeycode();

		void ProcessEvent(InputContext<bool>& event_) override;

		void DefaultBehaviour(ModifierContext& ctx) override;

		KeyboardBinding(const char* str);
		KeyboardBinding(const int sld);
		~KeyboardBinding() override;


	};

	int KeyboardBinding::GetKeycode()
	{
		return SDLKey;
	}

	void KeyboardBinding::ProcessEvent(InputContext<bool>& event_)
	{
		ModifierContext modifier_context;
		modifier_context.event_ = (event_.event_);

		bool processed = false;

		KeyPressedEvent* _pressedEvent;
		if (is<KeyPressedEvent>(event_.event_, &_pressedEvent))
		{

			if (this->SDLKey == _pressedEvent->GetKeyCode())
			{
				//We have a keystroke
				processed = true;
				modifier_context.bindingState_ = true;
				if (action_->IsContinuous())
				{
					natureState = ActionState::Performed;
				}
				else
				{
					if (_pressedEvent->GetRepeatCount() == 0)
						natureState = ActionState::Performed;
					else
						natureState = ActionState::Idle;
				}
			}
		}

		KeyReleasedEvent* _releasedEvent;
		if (is<KeyReleasedEvent>(event_.event_, &_releasedEvent))
		{

			if (this->SDLKey == _releasedEvent->GetKeyCode())
			{

				//We have a keystroke
				processed = true;
				modifier_context.bindingState_ = false;

				natureState = ActionState::Idle;

			}
		}

		if (processed)
			ProcessContext(&modifier_context);
	}

	void KeyboardBinding::DefaultBehaviour(ModifierContext& ctx)
	{
		ctx.outstate_ = natureState;
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
