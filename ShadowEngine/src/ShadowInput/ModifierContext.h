#pragma once
#include "ShadowInput/BindingContext.h"

namespace ShadowEngine::InputSystem {

	class ModifierContext
	{
	public:

		const EventSystem::ShadowEvent* event_;

		bool continuous_;
		bool bindingState_;
		ActionState outState_;
	};

}