#pragma once
#include "IInputBinding.h"
#include "ShadowEvents/ShadowEvent.h"
#include "BindingContext.h"


namespace ShadowInput
{

	class IShadowAction : public SHObject
	{
		SHObject_Base(IShadowAction)

	public:
		virtual ~IShadowAction() = default;
		virtual void ProcessEvent(ShadowEventSystem::ShadowEvent& e) = 0;

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
