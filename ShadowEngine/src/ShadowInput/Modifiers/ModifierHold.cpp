#include "ModifierHold.h"
#include "ShadowTime.h"

namespace ShadowInput
{
	void ModifierHold::ProcessInput(InputContext* ctx)
	{
		if(ctx->state_==ActionState::Started||ctx->state_==ActionState::Progress)
		{
			deltaTime += Time::deltaTime;
			if(deltaTime >= wait_)
			{
				ctx->state_ = ActionState::Progress;
			}
			else
			{
				ctx->state_ = ActionState::Progress;
			}
		}
	}
}
