#pragma once
#include "ShadowEvents/ShadowEvent.h"
#include <sstream>

namespace ShadowEventSystem {

	class MouseMovedEvent : public ShadowEvent
	{
		SHObject_Base(MouseMovedEvent)

	public:
		MouseMovedEvent(float x, float y, SDL_Event* ev)
			: m_MouseX(x), m_MouseY(y), ShadowEvent(ev)
		{
		}

		float GetX() const { return m_MouseX; }
		float GetY() const { return m_MouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}
	private:
		float m_MouseX, m_MouseY;
	};

	class MouseScrolledEvent : public ShadowEvent
	{
		SHObject_Base(MouseScrolledEvent)

	public:
		MouseScrolledEvent(float xOffset, float yOffset, SDL_Event* ev)
			: m_XOffset(xOffset), m_YOffset(yOffset), ShadowEvent(ev)
		{
		}

		float GetXOffset() const { return m_XOffset; }
		float GetYOffset() const { return m_YOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}

	private:
		float m_XOffset, m_YOffset;
	};

	class MouseButtonEvent : public ShadowEvent
	{
		SHObject_Base(MouseButtonEvent)

	public:
		int GetMouseButton() const { return m_Button; }

	protected:
		MouseButtonEvent(int button, SDL_Event* ev)
			: m_Button(button), ShadowEvent(ev)
		{
		}

		int m_Button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
		SHObject_Base(MouseButtonPressedEvent)

	public:
		MouseButtonPressedEvent(int button, SDL_Event* ev)
			: MouseButtonEvent(button, ev)
		{
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
		SHObject_Base(MouseButtonReleasedEvent)

	public:
		MouseButtonReleasedEvent(int button, SDL_Event* ev)
			: MouseButtonEvent(button, ev)
		{
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}
	};

}