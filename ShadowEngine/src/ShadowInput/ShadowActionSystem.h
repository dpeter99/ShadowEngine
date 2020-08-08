#pragma once
#include "ShadowEvents/IShadowEventListener.h"
#include <list>
#include "ShadowInput/ShadowAction.h"
#include "ShadowModules/ShadowModule.h"

namespace ShadowEngine::InputSystem
{
	/**
	 * This stores and processes the events
	 * \brief The Action system
	 */
	class ShadowActionSystem :
		public ShadowModule,
		public EventSystem::IShadowEventListener
	{
		

	public:
		static ShadowActionSystem* _instance;

		std::list<IShadowAction*> actions;

		ShadowActionSystem();
		~ShadowActionSystem();

		void AddEvent(IShadowAction* a);

		IShadowAction* GetAction(std::string name);



		void OnEvent(EventSystem::ShadowEvent& e) override;

		void PreInit() override {};
		void Init() override;
		void Update() override;
		void Render() override {};
		void LateRender() override {};

		std::string GetName() override { return  "ActionSystem"; };


		static void RegisterInspectors();

	};
}
