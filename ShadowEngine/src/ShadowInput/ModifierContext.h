#pragma once
#include "ShadowInput/BindingContext.h"

namespace ShadowInput {

	class ModifierContext
	{
	public:

		const ShadowEventSystem::ShadowEvent* event_;

		bool continuous_;
		bool bindingState_;
		ActionState outState_;
	};

}