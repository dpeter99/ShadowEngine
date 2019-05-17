#pragma once
namespace ShadowEventSystem {

	class IShadowEventSource
	{
	public:

		virtual void PollEvents() const = 0;

		IShadowEventSource();
		virtual ~IShadowEventSource();
	};
}