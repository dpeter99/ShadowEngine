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

			BindingContext<I> bindingContextA(event.event_, true);
			//Call the binding
			aBinding->ProcessEvent(bindingContextA);
			//Check if it was sucesfull
			if (bindingContextA.processed_) {
				data = bindingContextA.data_;
				aState = bindingContextA.outState_;
				processed = true;
			}

			BindingContext<I> bindingContextB(event.event_, true);
			//Call the binding
			bBinding->ProcessEvent(bindingContextB);
			//Check if it was sucesfull
			if (bindingContextB.processed_) {
				data = bindingContextB.data_;
				bState = bindingContextB.outState_;
				processed = true;
			}

			if(processed)
			{
				ModifierContext modCtx;
				modCtx.event_ = (event.event_);
				modCtx.continuous_ = event.continuous_;

				modCtx.bindingState_ = false;
			
				event.data_ = false;
			

				if(aState == bState)
				{
					event.outState_ = aState;

					if (aState == ActionState::Performed || aState == ActionState::Progress) {
						event.data_ = true;
						modCtx.bindingState_ = true;
					}
				}

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
