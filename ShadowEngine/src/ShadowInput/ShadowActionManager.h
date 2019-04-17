#pragma once
#include "ShadowEvents/IShadowEventListener.h"
#include <list>
#include "ShadowInput/ShadowAction.h"

namespace  ShadowInput {

	class ShadowActionManager :
		public IShadowEventListener
	{

		std::list<IShadowAction*> actions;

	public:
		static ShadowActionManager* _instance;

		void OnEvent(ShadowEvent& e) override;

		void AddEvent(IShadowAction* a);

		ShadowActionManager();
		~ShadowActionManager();
	};

}