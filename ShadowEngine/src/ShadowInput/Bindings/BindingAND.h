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

			ActionState aState;

			BindingContext<I> bindingContextA(event.event_, event.continuous_);
			//Call the binding
			aBinding->ProcessEvent(bindingContextA);
			//Check if it was sucesfull
			if (bindingContextA.processed_) {
				data = bindingContextA.data_;
				aState = bindingContextA.outState_;
				processed = true;
			}

			ActionState bState;

			BindingContext<I> bindingContextB(event.event_, event.continuous_);
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

				if(aState == bState)
				{
					event.outState_ = aState;

					if (aState == ActionState::Performed || aState == ActionState::Progress)
						modCtx.bindingState_ = true;
				}

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

	};

}
