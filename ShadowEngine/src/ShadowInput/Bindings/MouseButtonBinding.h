#pragma once
#include "ShadowInput/InputBinding.h"
#include "glm/vec2.hpp"
#include <SDL_mouse.h>


namespace ShadowEngine::InputSystem
{
	/**
	 * \brief Binding to a keyboard key press
	 */
	class MouseButtonBinding :
		public InputBinding<bool>
	{

		Uint8 button;

	public:
		MouseButtonBinding(Uint8 button) : button(button)
		{

		}

		void ProcessEvent(BindingContext<bool>& event) override;
		void DefaultBehaviour(ModifierContext& ctx) override;
	};


}
