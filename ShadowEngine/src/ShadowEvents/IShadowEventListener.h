#pragma once
#include "Events/KeyEvents.h"
class ShadowEvent;

namespace ShadowEventSystem {

#define EVENT_BIND(Event,Type,Func)					\
	if(Event.GetType() == Type::Type())				\
	{ Type *_event = dynamig_cast<Type>(Event);		\
	Func											\
	}


	class IShadowEventListener
	{
	public:

		virtual void OnEvent(ShadowEvent& e) = 0;

		IShadowEventListener() = default;
		~IShadowEventListener() = default;
	};
}