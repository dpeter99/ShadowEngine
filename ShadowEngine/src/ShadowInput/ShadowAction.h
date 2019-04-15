#pragma once
#include "InputBinding.h"

namespace ShadowInput {

	template<class T>
	class ShadowAction
	{

		bool active;
		//TODO: Delegates to activate
		
		InputBinding<T>* binding_;

	public:


		/**
		 * \brief Updates the Action with the event passed in
		 * \param e Event object
		 */
		void ProcessEvent(ShadowEvent& e);

		ShadowAction(std::string a, ShadowInput::InputBinding<T>* b, bool continous = false);
		~ShadowAction();
	};

	
}
