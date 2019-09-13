#pragma once
#include  "shpch.h"
#include "ShadowEvents/ShadowEvent.h"


namespace ShadowEngine::EventSystem::Events {

	class WindowResizeEvent : public ShadowEvent
	{
		SHObject_Base(WindowResizeEvent)

	public:
		WindowResizeEvent(unsigned int width, unsigned int height, SDL_Event* ev)
			: m_Width(width), m_Height(height), ShadowEvent(ev)
		{}

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}
	private:
		unsigned int m_Width, m_Height;
	};

	class WindowCloseEvent : public ShadowEvent
	{
		SHObject_Base(WindowCloseEvent)

	public:
		WindowCloseEvent(SDL_Event* ev): ShadowEvent(ev) {}
	};
}
