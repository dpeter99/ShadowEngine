#pragma once
#include "ShadowInput/InputBinding.h"

namespace ShadowEngine::InputSystem
{

	/**
	 * \brief This Binding only actives if either of the sub bindings are active
	 * \tparam I The type of the sub bindings
	 */
	template<class I>
	class BindingOR :
		public InputBinding<I>
	{
		SHObject_Base(BindingOR<I>);

		/**
		 * \brief The A side of the OR
		 */
		InputBinding<I>* aBinding;
		/**
		 * \brief The B side of the OR
		 */
		InputBinding<I>* bBinding;

		/**
		 * \brief The last state of A
		 */
		ActionState aState = ActionState::UnInit;

		/**
		 * \brief The last state of B
		 */
		ActionState bState = ActionState::UnInit;

	public:

		/**
		 * \brief Constructor for the BindingOR. The pointers will be freed up by the binding
		 * \param _a A side binding
		 * \param _b B side binding
		 */
		BindingOR(InputBinding<I>* _a, InputBinding<I>* _b) : aBinding(_a), bBinding(_b)
		{

		}

		/**
		 * \brief This should only be called by the Input system
		 */
		~BindingOR()
		{
			delete aBinding;
			delete bBinding;
		}


		void ProcessEvent(BindingContext<I>& event) override
		{
			bool processed = false;

			I data = I();

			ActionState aStateNew = aState;

			BindingContext<I> bindingContextA(event.event_, true);
			//Call the binding
			aBinding->ProcessEvent(bindingContextA);
			//Check if it was sucesfull
			if (bindingContextA.processed_) {
				data = bindingContextA.data_;
				aStateNew = bindingContextA.outState_;
				processed = true;
			}

			ActionState bStateNew = bState;

			BindingContext<I> bindingContextB(event.event_, true);
			//Call the binding
			bBinding->ProcessEvent(bindingContextB);
			//Check if it was sucesfull
			if (bindingContextB.processed_) {
				data = bindingContextB.data_;
				bStateNew = bindingContextB.outState_;
				processed = true;
			}

			if (processed)
			{
				ModifierContext modCtx;
				modCtx.event_ = (event.event_);
				modCtx.continuous_ = event.continuous_;

				modCtx.bindingState_ = false;

				event.data_ = data;


				//We only do anything if A OR B bindings are active
				if (aStateNew == ActionState::Performed || aStateNew == ActionState::Progress ||
					bStateNew == ActionState::Performed || bStateNew == ActionState::Progress)
				{
					//If the action is cont. than we replicate the State every time
					if (event.continuous_ || (InputBinding<I>::modifiers_.size() > 0 && InputBinding<I>::modifiers_.front()->RequiresContinuous()))
					{
						modCtx.bindingState_ = true;
						if (aStateNew == ActionState::Performed || aStateNew == ActionState::Progress) {
							event.outState_ = aStateNew;
						}else
						{
							event.outState_ = bStateNew;
						}
					}
					// If the action is a one time, than we fire a event than wait for any of them to change the state
					else
					{
						if (aStateNew != aState || bStateNew != bState) {
							modCtx.bindingState_ = true;
							event.outState_ = ActionState::Performed;
						}
					}
				}
				else
				{

					event.outState_ = event.continuous_ ? ActionState::Canceled : ActionState::Idle;
				}
					aState = aStateNew;
					bState = bStateNew;

					modCtx.outState_ = event.outState_;

					this->ProcessContext(event, modCtx);
				
			}
		}

		void DefaultBehaviour(ModifierContext& ctx) override
		{

		}


		/**
		 * \brief Gets the A binding
		 * \return Reference of the binding
		 */
		InputBinding<I>& GetABinding()
		{
			return *aBinding;
		}

		/**
		 * \brief Gets the B binding
		 * \return Reference of the binding
		 */
		InputBinding<I>& GetBBinding()
		{
			return *bBinding;
		}


		friend class BindingORInspector;
	};

}