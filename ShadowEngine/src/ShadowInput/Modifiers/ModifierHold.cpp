#include "shpch.h"

#include "ModifierHold.h"
#include "ShadowTime.h"

namespace ShadowInput
{
	float ModifierHold::GetWaitTime()
	{
		return wait_;
	}

	float ModifierHold::GetDeltaTime()
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
}
