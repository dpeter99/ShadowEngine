#pragma once
#include "ShadowInput/InputBinding.h"

namespace ShadowEngine::InputSystem
{
	/**
	 * \brief This Binding represents a 1D value, in a float
	 * \tparam I The type that the sub bindings will provide. It must have float addition and substraction operators
	 */
	template <class I>
	class Binding1D
		: public InputBinding<float>
	{
		SHObject_Base(Binding1D)

	private:

		/**
		 * \brief This is the positive side binding
		 */
		InputBinding<I>* pos;
		/**
		 * \brief This is the negative side binding
		 */
		InputBinding<I>* neg;

	public:

		/**
		 * \brief Constructor. The suplied pointers will be cleaned automatically.
		 * \param _positive Pointer to the positive binding
		 * \param _negative Pointer to the negative binding
		 */
		Binding1D<I>(InputBinding<I>* _positive, InputBinding<I>* _negative) : pos(_positive),
			neg(_negative)
		{
		}

		/**
		 * \brief This should only be called by the Input system
		 */
		~Binding1D()
		{
			delete pos;
			delete neg;
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
					if (event.continuous_ || (modifiers_.size() > 0 && modifiers_.front()->RequiresContinuous() && data != 0))
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

		/**
		 * \brief Gets the Positive side binding
		 * \return Reference of the Binding
		 */
		InputBinding<I>& GetPositiveBinding()
		{
			return *pos;
		}

		/**
		* \brief Gets the Negative side binding
		* \return Reference of the Binding
		*/
		InputBinding<I>& GetNegativeBinding()
		{
			return *neg;
		}
	};
}
