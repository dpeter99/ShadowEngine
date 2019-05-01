#pragma once
#include "shpch.h"

#include "ShadowInput/InputBinding.h"
#include "ShadowInput/BindingContext.h"
#include "ShadowEvents/Events/KeyEvents.h"
#include "ShadowInput/ModifierContext.h"

//class ModifierContext;

namespace ShadowInput
{
	class KeyboardBinding :
		public InputBinding<bool>
	{
		char* keycode;
		int SDLKey;

	public:

		int GetKeycode() const
		{
			return SDLKey;
		}

		void ProcessEvent(BindingContext<bool>& event_) override
		{

			ModifierContext modifier_context;
			modifier_context.event_ = (event_.event_);
			modifier_context.continuous_ = event_.continuous_;

			bool processed = false;

			if (event_.GetEvent()->GetType() == KeyPressedEvent::GetStaticType())
			{
				const KeyPressedEvent* _pressedEvent = dynamic_cast<const KeyPressedEvent*>(event_.event_);
				if (this->SDLKey == _pressedEvent->GetKeyCode())
				{
					//We have a keystroke
					processed = true;
					modifier_context.bindingState_ = true;
					event_.data_ = true;
				}
			}

			if (event_.GetEvent()->GetType() == KeyReleasedEvent::GetStaticType())
			{
				const KeyReleasedEvent* _releasedEvent = dynamic_cast<const KeyReleasedEvent*>(event_.event_);
				if (this->SDLKey == _releasedEvent->GetKeyCode())
				{
					//We have a keystroke
					processed = true;
					modifier_context.bindingState_ = false;
					event_.data_ = false;
				}
			}

			if (processed)
				ProcessContext(event_,modifier_context);

			event_.processed_ = processed;

		}

		void DefaultBehaviour(ModifierContext & ctx) override
		{
			if(ctx.bindingState_)
			{
				if (ctx.continuous_)
				{
					ctx.outState_ = ActionState::Performed;
				}
				else
				{
					if (dynamic_cast<const KeyPressedEvent*>(ctx.event_)->GetRepeatCount() == 0)
						ctx.outState_ = ActionState::Performed;
					else
						ctx.outState_ = ActionState::Idle;
				}
			}
			else
			{
				ctx.outState_ = ActionState::Idle;
			}

		}

		KeyboardBinding(const char* str)
		{
			keycode = new char;
			*keycode = *str;
		}

		KeyboardBinding(const int sdl)
		{
			SDLKey = sdl;
		}

		~KeyboardBinding() override
		{
			delete keycode;
		}


	};

	/*
	int KeyboardBinding::GetKeycode() const
	{
		return SDLKey;
	}
	*/

	/*
	void KeyboardBinding::ProcessEvent(BindingContext<bool>& event_)
	{
		ModifierContext modifier_context;
		modifier_context.event_ = (event_.event_);

		bool processed = false;


		if (event_.GetEvent()->GetType() == KeyPressedEvent::GetStaticType())
		{
			const KeyPressedEvent* _pressedEvent = dynamic_cast<const KeyPressedEvent*>(event_.event_);
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

		if (event_.GetEvent()->GetType() == KeyReleasedEvent::GetStaticType())
		{
			const KeyReleasedEvent* _releasedEvent = dynamic_cast<const KeyReleasedEvent*>(event_.event_);
			if (this->SDLKey == _releasedEvent->GetKeyCode())
			{

				//We have a keystroke
				processed = true;
				modifier_context.bindingState_ = false;

				natureState = ActionState::Idle;

			}
		}

		if (processed)
			ProcessContext(modifier_context);
	}
	*/

	/*
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
	*/

}
