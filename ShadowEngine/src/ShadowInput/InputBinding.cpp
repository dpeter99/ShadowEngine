#include "InputBinding.h"

namespace ShadowInput
{
	InputBinding* InputBinding::AddModifier(InputModifier* _m)
	{
		this->modifiers_.emplace_front(_m);

		return this;
	}

	InputModifier& InputBinding::GetModifier(int index)
	{
		std::list<InputModifier*>::iterator ptr;
		int i;
		for (i = 0, ptr = modifiers_.begin(); i < index && ptr != modifiers_.end(); i++, ptr++);

		if (ptr != modifiers_.end()) {

			
		}

		return **ptr;
	}

	int InputBinding::ModifierCount()
	{
		return modifiers_.size();
	}

	void InputBinding::ProcessContext(InputContext* ctx)
	{
		if (modifiers_.size() > 0) {
			for (auto modifier : modifiers_)
			{
				modifier->ProcessInput(ctx);
			}
		}
		else
		{
			DefaultBehaviour(ctx);
		}

		action_->SetState(ctx->outstate_);
	}
}
