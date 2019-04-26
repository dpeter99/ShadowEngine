#pragma once
#include "IInputBinding.h"


namespace ShadowInput
{

	class IShadowAction
	{
	public:
		virtual ~IShadowAction() = default;
		virtual void ProcessEvent(ShadowEvent& e) = 0;

		virtual void Update() = 0;

		virtual void AddEventListener(ActionState state) = 0;
		virtual void RemoveEventListener() = 0;

		virtual void SetActive(bool set) = 0;

		virtual std::string GetName() = 0;

		virtual ActionState GetState() = 0;
		virtual void SetState(ActionState state) = 0;

		virtual bool GetPerformed() = 0;

		virtual bool IsContinuous() = 0;
		virtual void SetContinuous(bool set) = 0;

		virtual IInputBinding& GetBinding() = 0;
	};
}
