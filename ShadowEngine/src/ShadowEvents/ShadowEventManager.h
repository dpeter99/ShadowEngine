#pragma once
#include <queue>
#include "ShadowEvents/ShadowEvent.h"
#include <list>
#include "ShadowEvents/IShadowEventSource.h"
#include "ShadowModules/ShadowModule.h"
#include "IShadowEventListener.h"

namespace ShadowEngine::EventSystem {

	class ShadowEventManager : public ShadowEngine::ShadowModule
	{
		static ShadowEventManager* instance;

		std::queue<ShadowEvent*> eventQueue;
		std::list<IShadowEventSource*> eventSources;
		std::list<IShadowEventListener*> eventConsumers;


		void PollEvents_();

		void PushNewEvent_(ShadowEvent* e);

		void ProcessEvents_();

		void AddNewEventSource_(IShadowEventSource* shadowEventSource);

		void AddNewEventListener_(IShadowEventListener* shadowEventSource);

	public:
		ShadowEventManager();
		~ShadowEventManager();

		void PreInit() override{};
		void Init() override;

		void Update() override {};
		void Render() override {};
		void LateRender() override {};

		std::string GetName() override { return "ShadowEventManager"; };

		static void PollEvents() { instance->PollEvents_(); };

		static void PushNewEvent(ShadowEvent* e) { instance->PushNewEvent_(e); };

		static void ProcessEvents() { instance->ProcessEvents_(); };

		static void AddNewEventSource(IShadowEventSource* shadowEventSource)
		{
			instance->AddNewEventSource_(shadowEventSource);
		};

		static void AddNewEventListener(IShadowEventListener* shadowEventListener)
		{
			instance->AddNewEventListener_(shadowEventListener);
		}

		;
	};

}