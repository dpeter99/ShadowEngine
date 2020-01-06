#include "shpch.h"

#include "MouseButtonBinding.h"

#include "ShadowEvents/Events/MouseEvents.h"

void ShadowEngine::InputSystem::MouseButtonBinding::ProcessEvent(BindingContext<bool>& event_)
{
	ModifierContext modifier_context;
	modifier_context.event_ = (event_.event_);
	modifier_context.continuous_ = event_.continuous_;

	bool processed = false;

	if (event_.GetEvent()->GetType() == EventSystem::Events::MouseButtonPressedEvent::Type())
	{
		const EventSystem::Events::MouseButtonPressedEvent* _pressedEvent = dynamic_cast<const EventSystem::Events::MouseButtonPressedEvent*>(event_.event_);
		if (this->button == _pressedEvent->GetMouseButton())
		{
			//We have a keystroke
			processed = true;
			modifier_context.bindingState_ = true;
			event_.data_ = true;
		}
	}

	if (event_.GetEvent()->GetType() == EventSystem::Events::MouseButtonReleasedEvent::Type())
	{
		const EventSystem::Events::MouseButtonReleasedEvent* _releasedEvent = dynamic_cast<const EventSystem::Events::MouseButtonReleasedEvent*>(event_.event_);
		if (this->button == _releasedEvent->GetMouseButton())
		{
			//We have a keystroke
			processed = true;
			modifier_context.bindingState_ = false;
			event_.data_ = false;
		}
	}

	if (processed)
		ProcessContext(event_, modifier_context);

	event_.processed_ = processed;
}

void ShadowEngine::InputSystem::MouseButtonBinding::DefaultBehaviour(ModifierContext& ctx)
{
	if (ctx.bindingState_)
	{
		if (ctx.continuous_) {
			ctx.outState_ = ActionState::Started;
		}
		else
		{
			ctx.outState_ = ActionState::Performed;
		}
	}
	else
	{
		ctx.outState_ = ActionState::Idle;
	}
}
