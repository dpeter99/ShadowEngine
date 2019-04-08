#include "KeyboardInput.h"
#include "Utility.h"
#include "ShadowEvents/IShadowEventListener.h"


void KeyboardInput::ProcessEvent(ShadowEvent& e)
{
	EVENT_BIND(e,KeyPressedEvent,
	{
		if(this->keycode[0] == _event->GetKeyCode())
		{
			
		}
	})
}

KeyboardInput::KeyboardInput()
{
}


KeyboardInput::~KeyboardInput()
{
}
