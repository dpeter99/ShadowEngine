#pragma once
#include <string>
#include <list>
#include "InputModifier.h"
#include "ShadowEvents/ShadowEvent.h"


class ShadowAction;

namespace ShadowInput {

	

	class InputBinding
	{
	protected:
		::ShadowAction* action_;

		std::list<InputModifier*> modifiers_;

		void ApplyModifiers();

	public:

		/**
		 * \brief Adds a new input modifier to the events modifier list
		 * \param _m The new modifier that is added
		 * \return Returns the same object so it can be chained
		 */
		InputBinding& AddModifier(const InputModifier& _m);

		/**
		 * \brief Processes a event
		 * \param event Event to process
		 */
		virtual void ProcessEvent(ShadowEvent& event) = 0;

		InputBinding();
		virtual ~InputBinding();
	};

}