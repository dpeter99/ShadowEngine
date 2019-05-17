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
		/**
		 * \brief The data that this binding holds, for example a float or a bool
		 */
		T data_;

		/**
		 * \brief A list of modifiers that process the binding
		 * This might be shortened to a single modifier
		 */
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


		/**
		 * \brief Adds a modifier to the binding. The binding will free up the memory of the modifier
		 * \param _m Pointer to the modifier
		 * \return Returns the binding itself for easier chaining
		 */
		InputBinding* AddModifier(InputModifier* _m) override
		{
			this->modifiers_.emplace_front(_m);

			return this;
		}


		/**
		 * \brief Gets a modifier form the list, at the given index
		 * \param index The index of the modifier
		 * \return Reference to the modifier
		 */
		InputModifier& GetModifier(int index) override
		{
			std::list<InputModifier*>::iterator ptr;
			int i;
			for (i = 0, ptr = modifiers_.begin(); i < index && ptr != modifiers_.end(); i++, ptr++);

			if (ptr != modifiers_.end()) {


			}

			return **ptr;
		}

		/**
		 * \brief Gets the number of the modifiers in this Binding
		 * \return Number of the modifiers
		 */
		int ModifierCount() override
		{
			return modifiers_.size();
		}

		/**
		 * \brief Gets the data form this binding
		 * \return The data
		 */
		T GetData()
		{
			return data_;
		}

		/**
		 * \brief Internal function to make the modifer handling easier. It 
		 * \param bdgCtx The binding context, got in ProcessEvent
		 * \param ctx The ModifierContect that will be given to the Modifiers to process
		 */
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

		InputBinding()
		{
			data_ = T();
		}
		
		virtual ~InputBinding()
		{
			for (auto modifier : modifiers_)
			{
				delete modifier;
			}
		}
	};

	
}
