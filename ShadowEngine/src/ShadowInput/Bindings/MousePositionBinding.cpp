#include "shpch.h"

#include "MousePositionBinding.h"
#include "ShadowEvents/Events/MouseEvents.h"

void ShadowEngine::InputSystem::MousePositionBinding::ProcessEvent(BindingContext<glm::vec2>& event)
{
	ModifierContext modifier_context;
	modifier_context.event_ = (event_.event_);
	modifier_context.continuous_ = event_.continuous_;

	bool processed = false;

	if (event_.GetEvent()->GetType() == EventSystem::Events::MouseMovedEvent::Type())
	{
		const EventSystem::Events::MouseMovedEvent* _pressedEvent = dynamic_cast<const EventSystem::Events::MouseMovedEvent*>(event_.event_);
		if (this->SDLKey == _pressedEvent->GetKeyCode())
		{
			//We have a keystroke
			processed = true;
			modifier_context.bindingState_ = true;
			event_.data_ = true;
		}
	}

	if (processed)
		ProcessContext(event_, modifier_context);

	event_.processed_ = processed;
}
