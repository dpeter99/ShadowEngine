#pragma once
#include "ShadowInput/InputBinding.h"
#include "ShadowEvents/ShadowEvent.h"
#include "ShadowInput/IShadowAction.h"
#include "ShadowInput/ShadowActionSystem.h"
#include "Callback.h"

namespace ShadowInput
{
	template <class T>
	class ShadowAction final :
		public IShadowAction
	{
		SHObject_Base(ShadowAction)

		std::string name;

		/**
		 * \brief weather this action is active and listening
		 */
		bool active;

		/**
		 * \brief Weather it was active in the current frame
		 */
		bool performed_b;

		bool performed_b_last;

		/**
		 * \brief The data state of the action
		 */
		T data;

		//TODO: Delegates to activate
		

		InputBinding<T>* binding_;
		ActionState state_;

		bool continuous_;

	public:
		Callback performed;

		ShadowAction(std::string a, InputBinding<T>* b, bool continuous = false)
		{
			name = a;
			binding_ = b;
			binding_->Init(this);
			state_ = ActionState::Idle;
			performed_b = false;
			continuous_ = continuous;

			ShadowInput::ShadowActionSystem::_instance->AddEvent(this);
		};

		~ShadowAction()
		{
			delete binding_;
		}


		/**
		 * \brief Updates the Action with the event passed in
		 * \param e Event object
		 */
		void ProcessEvent(ShadowEvent& e) override {
			BindingContext<T> inpCtx(&e, continuous_);
			inpCtx.bindingState_ = state_;
			inpCtx.outState_ = ActionState::UnInit;

			binding_->ProcessEvent(inpCtx);

			if(inpCtx.outState_ != UnInit)
			SetState(inpCtx.outState_);
		};

		void AddEventListener(ActionState state) override
		{
		};

		void RemoveEventListener() override
		{
		};

		void SetActive(bool set) override
		{
			active = set;
		};

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
			switch (state)
			{
			case ActionState::Idle:
				performed_b = false;
				break;
			case ActionState::Started:
				//TODO: call started
				performed_b = false;
				state = ActionState::Progress;
				break;
			case ActionState::Progress:
				performed_b = false;
				state = ActionState::Progress;
				break;
			case ActionState::Performed:
				//TODO: call performed
				performed();
				performed_b = true;
				state = ActionState::Idle;
				break;
			case ActionState::Canceled:
				//TODO: call canceled
				performed_b = false;
				state = ActionState::Idle;
				break;
			}
		}

		IInputBinding& GetBinding() override
		{
			return *binding_;
		}

		bool IsContinuous() override
		{
			return continuous_;
		}

		void SetContinuous(bool set) override
		{
			continuous_ = set;
		}

		bool GetPerformed() override
		{
			return performed_b;
		}

		void Update() override
		{
			if(performed_b_last && !continuous_)
			{
				performed_b = false;
			}
			performed_b_last = performed_b;
		}
	};
}
