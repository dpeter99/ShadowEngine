#pragma once
#include <string>
#include <list>
#include "ShadowInput/InputModifier.h"
#include "ShadowEvents/ShadowEvent.h"
#include "IShadowAction.h"
#include "IInputBinding.h"
#include "ModifierContext.h"


class ShadowAction;

namespace ShadowInput
{
	template <class T>
	class InputBinding:
		public IInputBinding
	{
		SHObject_Base(InputBinding)

	protected:
		T data_;

		IShadowAction* action_ = nullptr;
		std::list<InputModifier*> modifiers_;
	public:

		
		/**
		 * \brief Processes a event
		 * \param event Event to process
		 */
		virtual void ProcessEvent(BindingContext<T>& event) = 0;


		/**
		 * \brief The default behaviour of this binding without modifiers
		 * \param ctx The Input Context that this will use
		 */
		virtual  void DefaultBehaviour(ModifierContext& ctx) = 0;


		InputBinding* AddModifier(InputModifier* _m) override
		{
			this->modifiers_.emplace_front(_m);

			return this;
		}

		InputModifier& GetModifier(int index) override
		{
			std::list<InputModifier*>::iterator ptr;
			int i;
			for (i = 0, ptr = modifiers_.begin(); i < index && ptr != modifiers_.end(); i++, ptr++);

			if (ptr != modifiers_.end()) {


			}

			return **ptr;
		}

		int ModifierCount() override
		{
			return modifiers_.size();
		}

		T GetData()
		{
			return data_;
		}


		virtual void Init(IShadowAction* action)
		{
			action_ = action;
		}

		void ProcessContext(BindingContext<T>& bdgCtx ,ModifierContext& ctx)
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

			bdgCtx.outState_ = ctx.outState_;

			//action_->SetState(ctx.outstate_);
		}

		//InputBinding();
		virtual ~InputBinding()
		{
		}
	};

	
}
