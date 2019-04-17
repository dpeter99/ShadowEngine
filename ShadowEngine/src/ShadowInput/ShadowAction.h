#pragma once
#include "ShadowInput/InputBinding.h"
#include "ShadowEvents/ShadowEvent.h"

namespace ShadowInput {

	class IShadowAction
	{
	public:
		virtual  void ProcessEvent(ShadowEvent& e) = 0;

		virtual void AddEventListener(ActionState state) = 0;
		virtual void RemoveEventListener() = 0;

		virtual void SetActive(bool set) = 0;
	};


	template<class T>
	class ShadowAction :
		public IShadowAction
	{
		std::string name;

		bool active;
		//TODO: Delegates to activate
		
		ShadowInput::InputBinding<T> *binding_;

	public:


		/**
		 * \brief Updates the Action with the event passed in
		 * \param e Event object
		 */
		void ProcessEvent(ShadowEvent& e) override;


		void AddEventListener(ActionState state) {};
		void RemoveEventListener() {};
		void SetActive(bool set) {};

		ShadowAction(std::string a, ShadowInput::InputBinding<T>* b, bool continous = false);
		

		~ShadowAction();
	};

	
}
