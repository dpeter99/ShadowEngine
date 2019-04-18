#pragma once
#include "ShadowEvents/IShadowEventListener.h"
#include <list>
#include "ShadowInput/ShadowAction.h"
#include "ShadowModules/ShadowModule.h"

namespace ShadowInput
{
	class ShadowActionSystem :
		public ShadowModule,
		public IShadowEventListener
	{
		std::list<IShadowAction*> actions;

	public:
		static ShadowActionSystem* _instance;

		ShadowActionSystem();
		~ShadowActionSystem();

		void OnEvent(ShadowEvent& e) override;

		void AddEvent(IShadowAction* a);

		void Init() override;
		void Update() override;
		std::string GetName() override { return  "ActionSystem"; };



	};
}
