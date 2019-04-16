#pragma once
#include "InputBinding.h"
#include "ShadowEvents/ShadowEvent.h"

namespace ShadowInput {

	class IShadowAction
	{
	public:
		virtual  void ProcessEvent(ShadowEvent& e) = 0;
	};


	template<class T>
	class ShadowAction :
		public IShadowAction
	{
		std::string name;

		bool active;
		//TODO: Delegates to activate
		
		InputBinding<T>* binding_;

	public:


		/**
		 * \brief Updates the Action with the event passed in
		 * \param e Event object
		 */
		void ProcessEvent(ShadowEvent& e) override;

		ShadowAction(std::string a, ShadowInput::InputBinding<T>* b, bool continous = false);
		~ShadowAction();
	};

	
}
