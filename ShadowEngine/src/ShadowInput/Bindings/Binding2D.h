#pragma once
#include "ShadowInput/InputBinding.h"
#include "ShadowMap/ShadowWorld.h"
#include "ShadowMath/Vector2float.h"
#include "Util/Utility.h"

namespace ShadowEngine::InputSystem
{
	/**
	* \brief This Binding represents a 2D value, in a Vector2float
	* \tparam I The type that the sub bindings will provide. It must have float addition and substraction operators
	*/
	template <class I>
	class Binding2D
		: public InputBinding<ShadowMath::Vector2float>
	{
		/**
		 * \brief The positive X binding
		 */
		InputBinding<I>* xpos_;
		/**
		 * \brief The negative X binding
		 */
		InputBinding<I>* xneg_;

		/**
		 * \brief The positive Y binding
		 */
		InputBinding<I>* ypos_;
		/**
		 * \brief The negative Y binding
		 */
		InputBinding<I>* yneg_;

	public:

		/**
		 * \brief Constructor for the Binding2D. The pointers will be freed up by the binding
		 * \param _xpositive Positive X Direction
		 * \param _xnegative Negative X Direction
		 * \param _ypositive Positive Y Direction
		 * \param _ynegative Negative Y Direction
		 */
		Binding2D<I>(InputBinding<I>* _xpositive, InputBinding<I>* _xnegative,
			InputBinding<I>* _ypositive, InputBinding<I>* _ynegative)
			: xpos_(_xpositive), xneg_(_xnegative), ypos_(_ypositive), yneg_(_ynegative)
		{};

		/**
		 * \brief This should only be called by the Input system
		 */
		~Binding2D()
		{
			delete xpos_;
			delete xneg_;
			delete ypos_;
			delete yneg_;
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

			if (processed)
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

		/**
		 * \brief Gets the X positive binding
		 * \return Reference of the binding
		 */
		InputBinding<I>& GetXPositiveBinding()
		{
			return *xpos_;
		}

		/**
		 * \brief Gets the X negative binding
		 * \return Reference of the binding
		 */
		InputBinding<I>& GetXNegativeBinding()
		{
			return *xneg_;
		}

		/**
		 * \brief Gets the Y positive binding
		 * \return Reference of the binding
		 */
		InputBinding<I>& GetYPositiveBinding()
		{
			return *ypos_;
		}

		/**
		 * \brief Gets the Y negative binding
		 * \return Reference of the binding
		 */
		InputBinding<I>& GetYNegativeBinding()
		{
			return *yneg_;
		}
	};
}
