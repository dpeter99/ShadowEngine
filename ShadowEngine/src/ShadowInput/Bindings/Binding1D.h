#pragma once
#include "ShadowInput/InputBinding.h"

namespace ShadowInput
{
	template <class I>
	class Binding1D
		: public InputBinding<float>
	{
		SHObject_Base(Binding1D)

	private:
		InputBinding<I>* pos;
		InputBinding<I>* neg;

	public:

		Binding1D<I>(InputBinding<I>* _positive, InputBinding<I>* _negative) : pos(_positive),
			neg(_negative)
		{
		}

		~Binding1D()
		{
		}


		void ProcessEvent(BindingContext<float>& event) override
		{
			//Call both bindings in this composite binding
			//Check the values they returned
			 
			ModifierContext modCtx;
			modCtx.event_ = (event.event_);
			modCtx.continuous_ = event.continuous_;

			float data = 0;
			bool processed = false;

			//This is the positive direction binding
			//New binding context for the Positive binding
			BindingContext<I> bindingContextPos(event.event_,event.continuous_);
			//Call the binding
			pos->ProcessEvent(bindingContextPos);
			//Check if it was sucesfull
			if (bindingContextPos.processed_) {
				data += bindingContextPos.data_ ? 1 : 0;
				processed = true;
			}

			//This is the negative direction binding
			BindingContext<I> bindingContextNeg(event.event_, event.continuous_);
			neg->ProcessEvent(bindingContextNeg);
			if (bindingContextNeg.processed_) {
				data += -(bindingContextNeg.data_ ? 1 : 0);
				processed = true;
			}


			if (processed) {
				if (data != data_ && data != 0) {
					data_ = data;
					modCtx.bindingState_ = true;
				}
				else
				{
					if ((event.continuous_ || (modifiers_.size() > 0 && modifiers_.front()->RequieresContinous()) && data != 0))
					{
						modCtx.bindingState_ = true;
					}
					else
					{
						modCtx.bindingState_ = false;
					}

					if(data == 0)
					{
						data_ = 0;
					}
				}

				event.data_ = data_;

				ProcessContext(event, modCtx);
			}
		}

		void DefaultBehaviour(ModifierContext& ctx) override
		{
			if(ctx.continuous_)
			{
				if(data_ != 0)
				{
					ctx.outState_ = ActionState::Performed;
				}
				else
				{
					ctx.outState_ = ActionState::Idle;
				}
			}
			else
			{
				if(ctx.bindingState_)
				{
					ctx.outState_ = ActionState::Performed;
				}
				else
				{
					ctx.outState_ = ActionState::Idle;
				}
			}
		}

		InputBinding<I>& GetPositiveBinding()
		{
			return *pos;
		}

		InputBinding<I>& GetNegativeBinding()
		{
			return *neg;
		}
	};
}
