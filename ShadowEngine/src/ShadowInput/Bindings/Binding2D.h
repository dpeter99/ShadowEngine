#pragma once
#include "ShadowInput/InputBinding.h"
#include "ShadowMap/ShadowWorld.h"
#include "ShadowMath/Vector2float.h"
#include "Utility.h"

namespace ShadowInput
{
	template <class I>
	class Binding2D
		: public InputBinding<ShadowMath::Vector2float>
	{
		InputBinding<I>* xpos_;
		InputBinding<I>* xneg_;

		InputBinding<I>* ypos_;
		InputBinding<I>* yneg_;

	public:

		Binding2D<I>(InputBinding<I>* _xpositive, InputBinding<I>* _xnegative,
					InputBinding<I>* _ypositive, InputBinding<I>* _ynegative)
		: xpos_(_xpositive), xneg_(_xnegative), ypos_(_ypositive), yneg_(_ynegative)
		{};

		~Binding2D()
		{
			
		}

		void ProcessEvent(BindingContext<ShadowMath::Vector2float>& event) override
		{
			bool processed = false;

			float xDir = 0;

			BindingContext<I> xPosCtx(event.event_, event.continuous_);
			xpos_->ProcessEvent(xPosCtx);
			if (xPosCtx.processed_) {
//				xDir += xPosCtx.data_ ? 1 : 0;
				xDir += convert(xPosCtx.data_);
				processed = true;
			}

			BindingContext<I> xNegCtx(event.event_, event.continuous_);
			xneg_->ProcessEvent(xNegCtx);
			if (xNegCtx.processed_) {
				//xDir -= xNegCtx.data_ ? 1 : 0;
				xDir -= convert(xNegCtx.data_);
				processed = true;
			}

			float yDir = 0;

			BindingContext<I> yPosCtx(event.event_, event.continuous_);
			ypos_->ProcessEvent(yPosCtx);
			if (yPosCtx.processed_) {
				//yDir += yPosCtx.data_ ? 1 : 0;
				yDir += convert(yPosCtx.data_);
				processed = true;
			}

			BindingContext<I> yNegCtx(event.event_, event.continuous_);
			yneg_->ProcessEvent(yNegCtx);
			if (yNegCtx.processed_) {
				//yDir -= yNegCtx.data_ ? 1 : 0;
				yDir -= convert(yNegCtx.data_);
				processed = true;
			}

			if(processed)
			{
				ModifierContext modCtx;
				modCtx.event_ = (event.event_);
				modCtx.continuous_ = event.continuous_;

				 auto newdata = ShadowMath::Vector2float(xDir, yDir);
				 if (newdata != data_ && newdata != ShadowMath::Vector2float::zero) {
					 data_ = newdata;
					 modCtx.bindingState_ = true;
				 }
				 else
				 {
					 if ((event.continuous_ || modifiers_.size() > 0) && newdata != ShadowMath::Vector2float::zero)
					 {
						 modCtx.bindingState_ = true;
					 }
					 else
					 {
						 modCtx.bindingState_ = false;
					 }

					 if (newdata == ShadowMath::Vector2float::zero)
					 {
						 data_ = newdata;
					 }
				 }

				 event.data_ = data_;

				 ProcessContext(event, modCtx);
			}
		};

		void DefaultBehaviour(ModifierContext& ctx) override
		{
			if (ctx.continuous_)
			{
				if (data_ != ShadowMath::Vector2float::zero)
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
				if (ctx.bindingState_)
				{
					ctx.outState_ = ActionState::Performed;
				}
				else
				{
					ctx.outState_ = ActionState::Idle;
				}
			}
		}

		InputBinding<I>& GetXPositiveBinding()
		{
			return *xpos_;
		}

		InputBinding<I>& GetXNegativeBinding()
		{
			return *xneg_;
		}

		InputBinding<I>& GetYPositiveBinding()
		{
			return *ypos_;
		}

		InputBinding<I>& GetYNegativeBinding()
		{
			return *yneg_;
		}
	};
}
