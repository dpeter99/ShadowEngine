#pragma once
#include <queue>
#include "ShadowEvents/ShadowEvent.h"
#include <list>
#include "ShadowEvents/IShadowEventSource.h"
#include "ShadowModules/ShadowModule.h"

class ShadowEventManager : public ShadowModule
{
	static  ShadowEventManager* instance;

	std::queue<ShadowEvent*> eventQueue;
	std::list<IShadowEventSource*> eventSources;

	void PushNewEvent_(ShadowEvent* e);

	void AddNewEventSource_(IShadowEventSource* shadowEventSource);

public:
	ShadowEventManager();
	~ShadowEventManager();

	void Init() const override;

	static void PushNewEvent(ShadowEvent* e) { instance->PushNewEvent_(e); };

	static void AddNewEventSource(IShadowEventSource* shadowEventSource) { instance->AddNewEventSource_(shadowEventSource); };
};
