#pragma once
#include "ShadowInput/InputBinding.h"

namespace ShadowInput {

	/**
	 * \brief This Binding only actives when both of it's inputs are active
	 * \tparam I The type of the sub bindings
	 */
	template <class I>
	class BindingAND :
		public InputBinding<I>
	{
		SHObject_Base(BindingAND<I>)

		/**
		 * \brief The A side of the AND
		 */
		InputBinding<I>* aBinding;
		/**
		 * \brief The B side of the AND
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
		 * \brief Constructor for the BindingAND. The pointers will be freed up by the binding
		 * \param _a A side binding
		 * \param _b B side binding
		 */
		BindingAND<I>(InputBinding<I>* _a, InputBinding<I>* _b):aBinding(_a), bBinding(_b)
		{
			
		}

		/**
		 * \brief This should only be called by the Input system
		 */
		~BindingAND()
		{
			//TODO: clean
		}

		void ProcessEvent(BindingContext<I>& event) override
		{
			bool processed = false;

			I data;

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

			if(processed)
			{
				ModifierContext modCtx;
				modCtx.event_ = (event.event_);
				modCtx.continuous_ = event.continuous_;

				modCtx.bindingState_ = false;
			
				event.data_ = data;
				

				//We only do anything if A and B bindings are the same
				if (aStateNew == bStateNew)
				{
					

					//If the inputs are active we process them, all other cases are inactive
					if (aStateNew == ActionState::Performed || aStateNew == ActionState::Progress)
					{
						//If the action is cont. than we relicate the State every time
						if (event.continuous_ || (modifiers_.size() > 0 && modifiers_.front()->RequieresContinous()))
						{
							event.data_ = true;
							modCtx.bindingState_ = true;
							event.outState_ = aState;
						}

						// If the action is a one time, than we fire a event than wait for them to leave that state
						else
						{
							if (aStateNew != aState || bStateNew != bState) {
								event.data_ = true;
								modCtx.bindingState_ = true;
								event.outState_ = ActionState::Performed;
							}
						}
					}
				}
				else if(aState == bState)
				{
					if (aState == ActionState::Performed || aState == ActionState::Progress)
					{
						event.outState_ = event.continuous_ ? ActionState::Canceled : ActionState::Idle;
					}

				}
				aState = aStateNew;
				bState = bStateNew;
				/*
					if (aState == ActionState::Performed || aState == ActionState::Progress)
					{
						if (aStateNew != ActionState::Performed || bStateNew != ActionState::Performed) {
						event.data_ = true;
						modCtx.bindingState_ = true;
							}

					}
				
				}
				*/
				modCtx.outState_ = event.outState_;

				ProcessContext(event, modCtx);
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


		friend class BindingANDInspector;
	};

}
