#include "ShadowEventManager.h"
#include "Platform/SDL/SDLEventSource.h"


ShadowEventManager* ShadowEventManager::instance = nullptr;

ShadowEventManager::ShadowEventManager()
{
	instance = this;

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

void ShadowEventManager::Init()
{
	//instance = new ShadowEventManager();
}

void ShadowEventManager::PollEvents_()
{
	for (auto var : eventSources)
	{
		var->PollEvents();
	}
}

void ShadowEventManager::PushNewEvent_(ShadowEvent* e)
{
	this->eventQueue.push(e);
}

void ShadowEventManager::ProcessEvents_()
{
	while(!eventQueue.empty())
	{
		auto e = eventQueue.front();
		for (auto listener : eventConsumers)
		{
			listener->OnEvent(*e);
		}
		eventQueue.pop();
	}
}

void ShadowEventManager::AddNewEventSource_(IShadowEventSource* shadowEventSource)
{
	eventSources.emplace_back(shadowEventSource);
}

void ShadowEventManager::AddNewEventListener_(IShadowEventListener* shadowEventSource)
{
	eventConsumers.emplace_back(shadowEventSource);
}


