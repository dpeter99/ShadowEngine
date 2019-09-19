#pragma once
#include "ShadowInput/InputModifier.h"

namespace ShadowEngine::InputSystem
{
	/**
	 * \brief Hold modifier. Only activates when the binding has been active for the specified time
	 */
	class ModifierHold :
		public InputModifier
	{
		SHObject_Base(ModifierHold)

		/**
		 * \brief The time it waits
		 */
		double wait_;

		/**
		 * \brief The time spent active
		 */
		double deltaTime;

	public:

		/**
		 * \brief Gets the time this will wait for
		 * \return 
		 */
		double GetWaitTime();

		/**
		 * \brief Gets the current delta time.
		 * \return 
		 */
		double GetDeltaTime();

		void ProcessInput(ModifierContext& ctx) override;

		/**
		 * \brief Constructor, gets the time it should wait
		 * \param time Wait time
		 */
		ModifierHold(const double time) : InputModifier(), wait_(time), deltaTime(0)
		{
			
		};

		~ModifierHold()
		{
			
		}

		bool RequiresContinuous() override;
	};
}
