#pragma once

namespace ShadowEngine::Rendering {

	/**
	 * \brief A list of commands to be submitted to a CommandQueue
	 */
	class CommandList
	{
	public:
		virtual ~CommandList() = default;
		
		virtual void Reset() = 0;

	public:
		static Ref<CommandList> Create();
	};

}