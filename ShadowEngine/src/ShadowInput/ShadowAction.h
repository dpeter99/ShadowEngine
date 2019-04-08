#pragma once
#include "InputEventSource.h"

class ShadowAction
{

	bool active;
	//TODO: Delegates to activate
	//TODO: link to the activation tree
	InputEventSource source_;

public:
	ShadowAction();
	~ShadowAction();
};

