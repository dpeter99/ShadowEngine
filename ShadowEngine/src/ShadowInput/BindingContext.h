#pragma once
#include "ShadowEvents/ShadowEvent.h"

namespace ShadowInput {
	/**
	 * \brief Possible states of a Action
	 */
	enum ActionState
	{
		/**
		 * \brief Default state
		 */
		UnInit,
		/**
		 * \brief Idle binding
		 */
		Idle,
		Started, //Shadow state
		Progress,
		Performed, //Shadow state
		Canceled,
	};

	/**
	 * This stores the data passed to input bindings.
	 * \brief Context of the Binding calls
	 * \tparam T The type of the data stored
	 */
	template<class T>
	class BindingContext
	{
	public:
		/**
		 * \brief The event that triggered this call
		 */
		const ShadowEventSystem::ShadowEvent* event_;

		/**
		 * \brief Weather this binding should behave continuously
		 */
		bool continuous_;

		/**
		 * \brief The state of the binding
		 */
		bool bindingState_;

		/**
		 * \brief The output state form this binding
		 */
		ActionState outState_;

		/**
		 * \brief The data this binding gives the action
		 */
		T data_;

		/**
		 * \brief If the binding actually activated
		 */
		bool processed_;

		BindingContext(const ShadowEventSystem::ShadowEvent* event, bool cont)
		{
			event_ = event;
			continuous_ = cont;
			bindingState_ = false;
			data_ = T();
			processed_ = false;
			outState_ = ActionState::UnInit;
		}

		~BindingContext()
		{
		}

		const ShadowEventSystem::ShadowEvent* GetEvent() { return event_; };
	};
}