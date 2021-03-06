#pragma once
#include "shpch.h"

#include "ShadowInput/InputBinding.h"
#include "ShadowInput/BindingContext.h"
#include "ShadowEvents/Events/KeyEvents.h"
#include "ShadowInput/ModifierContext.h"

namespace ShadowEngine::InputSystem
{
	/**
	 * \brief Binding to a keyboard key press
	 */
	class KeyboardBinding :
		public InputBinding<bool>
	{
		//char* keycode;
		int SDLKey;

	public:

		/**
		 * \brief Gets the keycode of this binding
		 * \return Key code
		 */
		int GetKeycode() const
		{
			return SDLKey;
		}

		void ProcessEvent(BindingContext<bool>& event_)
		{

			ModifierContext modifier_context;
			modifier_context.event_ = (event_.event_);
			modifier_context.continuous_ = event_.continuous_;

			bool processed = false;

			if (event_.GetEvent()->GetType() == EventSystem::Events::KeyPressedEvent::Type())
			{
				const EventSystem::Events::KeyPressedEvent* _pressedEvent = dynamic_cast<const EventSystem::Events::KeyPressedEvent*>(event_.event_);
				if (this->SDLKey == _pressedEvent->GetKeyCode())
				{
					//We have a keystroke
					processed = true;
					modifier_context.bindingState_ = true;
					event_.data_ = true;
				}
			}

			if (event_.GetEvent()->GetType() == EventSystem::Events::KeyReleasedEvent::Type())
			{
				const EventSystem::Events::KeyReleasedEvent* _releasedEvent = dynamic_cast<const EventSystem::Events::KeyReleasedEvent*>(event_.event_);
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
					if (dynamic_cast<const EventSystem::Events::KeyPressedEvent*>(ctx.event_)->GetRepeatCount() == 0)
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

		/**
		 * \brief Constructor, using a SDL scancode for the key
		 * \param sdl SDL scancode
		 */
		KeyboardBinding(const int sdl)
		{
			SDLKey = sdl;
		}

		/**
		 * \brief This should only be called by the Input system
		 */
		~KeyboardBinding() override
		{
			//TODO: clean
		}


	};
}
