#include "ShadowAction.h"

namespace ShadowInput {

	template <class T>
	void ShadowAction<T>::ProcessEvent(ShadowEvent& e)
	{
		binding_->ProcessEvent(e);
	}

}