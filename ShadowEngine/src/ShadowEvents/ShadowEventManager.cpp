#include "ShadowEventManager.h"
#include "Platform/SDL/SDLEventSource.h"


ShadowEventManager::ShadowEventManager()
{
	IShadowEventSource* s = new SDLEventSource();
	AddNewEventSource(s);
}


ShadowEventManager::~ShadowEventManager()
{
	for (auto eventSource : eventSources)
	{
		delete eventSource;
	}
}

void ShadowEventManager::PushNewEvent(ShadowEvent* e)
{
	this->eventQueue.push(e);
}

void ShadowEventManager::AddNewEventSource(IShadowEventSource* shadowEventSource)
{
	eventSources.emplace_back(shadowEventSource);
}


