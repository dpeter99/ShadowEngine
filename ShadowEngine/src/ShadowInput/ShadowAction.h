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
		SHObject_Base(ShadowAction<T>)

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
		friend class InputActionInspector;

		Callback performed;

		ShadowAction(std::string a, InputBinding<T>* b, bool continuous = false)
		{
			name = a;
			binding_ = b;
			binding_->Init(this);
			state_ = ActionState::Idle;
			performed_b = false;
			continuous_ = continuous;

			data = T();

			ShadowInput::ShadowActionSystem::_instance->AddEvent(this);
		};

		~ShadowAction()
		{
			//delete binding_;
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
			{
				SetState(inpCtx.outState_);
				data = inpCtx.data_;
			}
		};

		//TODO: Change this to c# style event subsciption
		void AddEventListener(ActionState state) override
		{
		};
		
		void RemoveEventListener() override
		{
		};

		//TODO: Should this be exposed?
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

		//TODO: Should this be exposed?
		void SetState(ActionState state) override
		{
			switch (state)
			{
			case ActionState::Idle:
				performed_b = false;
				state_ = ActionState::Idle;
				break;
			case ActionState::Started:
				performed_b = false;
				Started();
				state_ = ActionState::Progress;
				break;
			case ActionState::Progress:
				performed_b = false;
				if (state_ != ActionState::Progress)
					Started();

				Progress();

				state_ = ActionState::Progress;
				break;
			case ActionState::Performed:
				if (state_ != ActionState::Performed && state_ != ActionState::Progress && performed_b == false)
					Started();

				Performed();
				performed_b = true;

				state_ = ActionState::Idle;
				break;
			case ActionState::Canceled:
				Canceled();
				performed_b = false;
				state_ = ActionState::Idle;
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

		//TODO: Should this be exposed?
		void SetContinuous(bool set) override
		{
			continuous_ = set;
		}

		bool GetPerformed() override
		{
			return performed_b;
		}

		const T GetData()
		{
			return data;
		}

		void Update() override
		{
			if(performed_b_last && !continuous_)
			{
				performed_b = false;
			}
			performed_b_last = performed_b;
		}


		void Performed()
		{
			std::cout << GetName() << " Was performed !" << std::endl;
		}

		void Started()
		{
			std::cout << GetName() << " Was started !" << std::endl;
		}

		void Progress()
		{
			std::cout << GetName() << " Progress !" << std::endl;
		}

		void Canceled()
		{
			std::cout << GetName() << " Was canceled !" << std::endl;
		}
	};
}
