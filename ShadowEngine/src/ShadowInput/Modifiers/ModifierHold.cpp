#include "shpch.h"

#include "ModifierHold.h"
#include "ShadowTime.h"

namespace ShadowEngine::InputSystem
{
	double ModifierHold::GetWaitTime()
	{
		return wait_;
	}

	double ModifierHold::GetDeltaTime()
	{
		return deltaTime;
	}

	void ModifierHold::ProcessInput(ModifierContext& ctx)
	{
		if(!ctx.bindingState_)
		{
			ctx.outState_ = ActionState::Canceled;
			deltaTime = 0;
		}
		else if(ctx.bindingState_)
		{
			deltaTime += Time::deltaTime;
			if(deltaTime >= wait_)
			{
				ctx.outState_ = ActionState::Performed;
				deltaTime = 0;
			}
			else
			{
				ctx.outState_ = ActionState::Progress;
			}
		}
	}

	bool ModifierHold::RequiresContinuous()
	{
		return true;
	}
}
