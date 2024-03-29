#include "shpch.h"

#include "ShadowActionSystem.h"
#include "ShadowEvents/ShadowEventManager.h"

namespace ShadowEngine::InputSystem
{
	ShadowActionSystem* ShadowActionSystem::_instance = nullptr;

	void ShadowActionSystem::OnEvent(EventSystem::ShadowEvent& e)
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
		EventSystem::ShadowEventManager::AddNewEventListener(this);

		RegisterInspectors();
	}
	
	void ShadowActionSystem::Update()
	{
		for (auto action : actions)
		{
			action->Update();
		}
	}
	
	ShadowActionSystem::ShadowActionSystem()
	{
		_instance = this;
	}


	ShadowActionSystem::~ShadowActionSystem()
	{
		for (auto action : actions)
		{
			delete action;
		}
	}
}
