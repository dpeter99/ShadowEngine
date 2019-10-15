#pragma once

namespace ShadowEngine::Rendering {
	class CommandList;

	/**
	 * \brief The execution queue witch can execute a Command List
	 */
	class CommandQueue
	{
	public:
		virtual void Execute(Ref<CommandList> commandList) = 0;
	public:
		virtual ~CommandQueue() = default;
		
		static Ref<CommandQueue> Create();
	};

}
