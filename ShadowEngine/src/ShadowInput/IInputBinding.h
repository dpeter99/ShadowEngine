#pragma once


namespace ShadowInput
{
	class IInputBinding
	{
		public:
		/**
		 * \brief Adds a new input modifier to the events modifier list
		 * \param _m The new modifier that is added
		 * \return Returns the same object so it can be chained
		 */
		virtual IInputBinding* AddModifier(InputModifier* _m) = 0;

		/**
		 * \brief returns the modifier at the index
		 * \param index The index of the modifier needed
		 * \return The modifier requested
		 */
		virtual InputModifier& GetModifier(int index) = 0;


		virtual int ModifierCount() = 0;
		

	};
}