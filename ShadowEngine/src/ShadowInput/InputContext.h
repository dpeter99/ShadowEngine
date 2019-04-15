#pragma once
#include "InputBinding.h"
#include "ShadowAction.h"

template<class T>
class InputContext
{
public:
	ShadowEvent* event_;

	ShadowInput::ShadowAction<T>* action_;

	ActionState state_;
	T data_;



	InputContext();
	~InputContext();

	ShadowEvent* GetEvent() { return event_; };



};


enum ActionState
{
	Idle,
	Started,
	Progress,
	Ended,
	Canceled,
};
