#pragma once
#include "ShadowInput/InputBinding.h"

namespace ShadowInput {

	template <class I>
	class BindingAND :
		public InputBinding<I>
	{
		SHObject_Base(BindingAND<I>)

		InputBinding<I>* aBinding;
		InputBinding<I>* bBinding;

		ActionState aState = ActionState::UnInit;
		ActionState bState = ActionState::UnInit;

	public:
		BindingAND<I>(InputBinding<I>* _a, InputBinding<I>* _b):aBinding(_a), bBinding(_b)
		{
			
		}

		~BindingAND()
		{
			
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


		InputBinding<I>& GetABinding()
		{
			return *aBinding;
		}

		InputBinding<I>& GetBBinding()
		{
			return *bBinding;
		}


		friend class BindingANDInspector;
	};

}
