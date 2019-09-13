#pragma once
#include "BindingContext.h"
#include "ShadowInput/ModifierContext.h"
#include "Core/SHObject.h"

namespace ShadowEngine::InputSystem
{

	class InputModifier : public ShadowEngine::SHObject
	{
		SHObject_Base(InputModifier)

	public:

		/**
		 * \brief Processes a event. Called after the binding processed it.
		 * \param ctx Modifier context that provides data  about the event
		 */
		virtual void ProcessInput(ModifierContext& ctx) = 0;


		/**
		 * \brief Weather this modifier needs the binding to act continuous
		 * \return true if it needs continuous binding
		 */
		virtual bool RequiresContinuous() = 0;

		InputModifier()
		{
			
		};
		virtual  ~InputModifier()
		{
			
		};
	};

}
