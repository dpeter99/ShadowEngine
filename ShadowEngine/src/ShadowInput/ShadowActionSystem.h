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
		

	public:
		static ShadowActionSystem* _instance;

		std::list<IShadowAction*> actions;

		ShadowActionSystem();
		~ShadowActionSystem();

		void AddEvent(IShadowAction* a);

		IShadowAction* GetAction(std::string name);



		void OnEvent(ShadowEvent& e) override;

		void Init() override;

		void Update() override;

		std::string GetName() override { return  "ActionSystem"; };



	};
}
