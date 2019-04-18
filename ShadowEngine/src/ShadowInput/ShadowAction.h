#pragma once
#include "ShadowInput/InputBinding.h"
#include "ShadowEvents/ShadowEvent.h"
#include "ShadowInput/IShadowAction.h"
#include "ShadowInput/ShadowActionSystem.h"

namespace ShadowInput
{
	template <class T>
	class ShadowAction :
		public IShadowAction
	{
		std::string name;

		bool active;
		//TODO: Delegates to activate

		InputBinding<T>* binding_;
		ActionState state_;

	public:


		/**
		 * \brief Updates the Action with the event passed in
		 * \param e Event object
		 */
		void ProcessEvent(ShadowEvent& e) override {
			binding_->ProcessEvent(e);
		};



		void AddEventListener(ActionState state) override
		{
		};

		void RemoveEventListener() override
		{
		};

		void SetActive(bool set) override
		{
		};

		ShadowAction(std::string a, InputBinding<T>* b, bool continous = false)
		{
			name = a;
			binding_ = b;
			binding_->Init(this);

			ShadowInput::ShadowActionSystem::_instance->AddEvent(this);
		};

		~ShadowAction() 
		{
			delete binding_;
		}

		std::string GetName() override
		{
			return name;
		};

		ActionState GetState() override
		{
			return state_;
		}

		void SetState(ActionState state) override
		{
			state_ = state;
		};
	};
}
