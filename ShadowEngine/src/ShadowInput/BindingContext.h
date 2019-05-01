#pragma once
#include "ShadowEvents/ShadowEvent.h"

//#include "ShadowAction.h"

enum ActionState
{
	UnInit,
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

	bool continuous_;

	bool bindingState_;
	ActionState outState_;
	T data_;

	bool processed_;

	BindingContext(const ShadowEvent* event, bool cont)
	{
		event_ = event;
		continuous_ = cont;
		data_ = 0;
		processed_ = false;
	}

	~BindingContext()
	{
	}

	const ShadowEvent* GetEvent() { return event_; };
};
