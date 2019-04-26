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

	void ModifierHold::ProcessInput(BindingContext* ctx)
	{
		if(ctx->bindingState_ == false)
		{
			ctx->outstate_ = ActionState::Canceled;
			deltaTime = 0;
		}
		else if(ctx->bindingState_==true)
		{
			deltaTime += Time::deltaTime;
			if(deltaTime >= wait_)
			{
				ctx->outstate_ = ActionState::Performed;
				deltaTime = 0;
			}
			else
			{
				ctx->outstate_ = ActionState::Progress;
			}
		}
	}
}
