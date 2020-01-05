#pragma once
#include "ShadowInput/InputBinding.h"
#include "glm/vec2.hpp"


namespace ShadowEngine::InputSystem
{
	/**
	 * \brief Binding to a keyboard key press
	 */
	class MousePositionBinding :
		public InputBinding<glm::vec2>
	{
	public:
		void ProcessEvent(BindingContext<glm::vec2>& event) override;
		void DefaultBehaviour(ModifierContext& ctx) override;
	};


}
