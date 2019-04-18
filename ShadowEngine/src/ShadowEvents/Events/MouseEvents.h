#pragma once
#include "ShadowEvents/ShadowEvent.h"
#include <sstream>

class MouseMovedEvent : public ShadowEvent
{
public:
	MouseMovedEvent(float x, float y)
		: m_MouseX(x), m_MouseY(y)
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

	EVENT_CLASS_TYPE(MouseMoved)
private:
	float m_MouseX, m_MouseY;
};

class MouseScrolledEvent : public ShadowEvent
{
public:
	MouseScrolledEvent(float xOffset, float yOffset)
		: m_XOffset(xOffset), m_YOffset(yOffset)
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

	EVENT_CLASS_TYPE(MouseScrolled)
private:
	float m_XOffset, m_YOffset;
};

class MouseButtonEvent : public ShadowEvent
{
public:
	int GetMouseButton() const { return m_Button; }

protected:
	MouseButtonEvent(int button)
		: m_Button(button)
	{
	}

	int m_Button;
};

class MouseButtonPressedEvent : public MouseButtonEvent
{
public:
	MouseButtonPressedEvent(int button)
		: MouseButtonEvent(button)
	{
	}

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseButtonPressedEvent: " << m_Button;
		return ss.str();
	}

	EVENT_CLASS_TYPE(MouseButtonPressed)
};

class MouseButtonReleasedEvent : public MouseButtonEvent
{
public:
	MouseButtonReleasedEvent(int button)
		: MouseButtonEvent(button)
	{
	}

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseButtonReleasedEvent: " << m_Button;
		return ss.str();
	}

	EVENT_CLASS_TYPE(MouseButtonReleased)
};
