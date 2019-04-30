#pragma once
#include "ShadowEvents/ShadowEvent.h"

//#include "ShadowAction.h"

enum ActionState
{
	Idle,
	Started, //Shadow state
	Progress,
	Performed, //Shadow state
	Canceled,
};

class ShadowAction;

template<class T>
class BindingContext
{
public:
	const ShadowEvent* event_;

	//ShadowInput::ShadowAction<T>* action_;

	bool bindingState_;
	ActionState outstate_;
	T data_;


	BindingContext();
	~BindingContext();

	const ShadowEvent* GetEvent() { return event_; };
};
