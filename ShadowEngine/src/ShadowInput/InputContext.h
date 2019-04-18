#pragma once
#include "ShadowEvents/ShadowEvent.h"

//#include "ShadowAction.h"

enum ActionState
{
	Idle,
	Started,
	Progress,
	Ended,
	Canceled,
};

class ShadowAction;

//template<class T>
class InputContext
{
public:
	ShadowEvent* event_;

	//ShadowInput::ShadowAction<T>* action_;

	ActionState state_;
	//T data_;


	InputContext();
	~InputContext();

	ShadowEvent* GetEvent() { return event_; };
};
