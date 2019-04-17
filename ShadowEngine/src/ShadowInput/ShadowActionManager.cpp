#include "ShadowActionManager.h"

namespace ShadowInput {

	ShadowActionManager* ShadowActionManager::_instance = nullptr;

	void ShadowActionManager::OnEvent(ShadowEvent& e)
	{
		for (auto action : actions)
		{
			action->ProcessEvent(e);
		}
	}

	ShadowActionManager::ShadowActionManager()
	{
		_instance = this;
	}


	ShadowActionManager::~ShadowActionManager()
	{
	}

}