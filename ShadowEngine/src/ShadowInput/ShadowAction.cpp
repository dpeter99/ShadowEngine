#include "ShadowAction.h"


namespace ShadowInput {

	template <class T>
	void ShadowAction<T>::ProcessEvent(ShadowEvent& e)
	{
		binding_->ProcessEvent(e);
	}

	template <class T>
	ShadowAction<T>::ShadowAction(std::string a, ShadowInput::InputBinding<T>* b, bool continous)
	{
		name = a;
		binding_ = b;

		ShadowInput::ShadowActionManager::_instance->AddEvent(this);
	}

	template <class T>
	ShadowAction<T>::~ShadowAction()
	{
		delete binding_;
	}
}
