#pragma once
#include "Events/KeyEvents.h"
class ShadowEvent;

#define EVENT_BIND(Event,Type,Func)		\
	Type *_event;					\
	if(is<Type>(Event, &_event))	\
	Func	\
		
	


class IShadowEventListener
{
public:

	virtual void OnEvent(ShadowEvent& e) = 0;

	IShadowEventListener() = default;
	~IShadowEventListener() = default;
};

