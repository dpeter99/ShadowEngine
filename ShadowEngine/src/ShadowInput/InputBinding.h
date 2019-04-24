#pragma once
#include <string>
#include <list>
#include "ShadowInput/InputModifier.h"
#include "ShadowEvents/ShadowEvent.h"
#include "IShadowAction.h"


class ShadowAction;

namespace ShadowInput
{
	//template <class T>
	class InputBinding
	{
	protected:
		IShadowAction* action_;
		std::list<InputModifier*> modifiers_;
	public:

		/**
		 * \brief Adds a new input modifier to the events modifier list
		 * \param _m The new modifier that is added
		 * \return Returns the same object so it can be chained
		 */
		InputBinding* AddModifier(InputModifier* _m);

		/**
		 * \brief Processes a event
		 * \param event Event to process
		 */
		virtual void ProcessEvent(const ShadowEvent& event) = 0;

		virtual  void DefaultBehaviour(InputContext* ctx) = 0;

		virtual void Init(IShadowAction* action)
		{
			action_ = action;
		}

		InputModifier& GetModifier(int i);

		int ModifierCount();

		void ProcessContext(InputContext* ctx);

		//InputBinding();
		virtual ~InputBinding()
		{
		}
	};

	
}
