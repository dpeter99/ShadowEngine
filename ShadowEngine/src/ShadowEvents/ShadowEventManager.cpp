#include "ShadowEventManager.h"
#include "Platform/SDL/SDLEventSource.h"


ShadowEventManager* ShadowEventManager::instance = nullptr;

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

void ShadowEventManager::Init() const
{
	//instance = new ShadowEventManager();
}

void ShadowEventManager::PushNewEvent_(ShadowEvent* e)
{
	this->eventQueue.push(e);
}

void ShadowEventManager::AddNewEventSource_(IShadowEventSource* shadowEventSource)
{
	eventSources.emplace_back(shadowEventSource);
}


