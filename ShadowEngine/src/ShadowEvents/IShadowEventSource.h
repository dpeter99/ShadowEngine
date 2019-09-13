#pragma once
namespace ShadowEngine::EventSystem {

	class IShadowEventSource
	{
	public:

		virtual void PollEvents() const = 0;

		IShadowEventSource();
		virtual ~IShadowEventSource();
	};
}