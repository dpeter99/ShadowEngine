#include "ShadowActionSystem.h"
#include "ShadowEvents/ShadowEventManager.h"

namespace ShadowInput
{
	ShadowActionSystem* ShadowActionSystem::_instance = nullptr;

	void ShadowActionSystem::OnEvent(ShadowEvent& e)
	{
		for (auto action : actions)
		{
			action->ProcessEvent(e);
		}
	}

	void ShadowActionSystem::AddEvent(IShadowAction* a)
	{
		this->actions.emplace_back(a);
	}

	void ShadowActionSystem::Init()
	{
		ShadowEventManager::AddNewEventListener(this);
	}

	ShadowActionSystem::ShadowActionSystem()
	{
		_instance = this;
	}


	ShadowActionSystem::~ShadowActionSystem()
	{
	}
}
