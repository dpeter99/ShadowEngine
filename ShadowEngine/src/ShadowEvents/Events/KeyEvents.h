#pragma once

#include "ShadowEvents/ShadowEvent.h"
#include <sstream>
#include <winerror.h>

class KeyEvent : public ShadowEvent
{
public:
	int GetKeyCode() const { return m_KeyCode; }

protected:
	KeyEvent(int keycode)
		: m_KeyCode(keycode)
	{
	}

	int m_KeyCode;
};

class KeyPressedEvent : public KeyEvent
{
public:
	KeyPressedEvent(int keycode, int repeatCount)
		: KeyEvent(keycode), m_RepeatCount(repeatCount)
	{
	}

	int GetRepeatCount() const { return m_RepeatCount; }

	EVENT_CLASS_TYPE(EventSource::EventCategoryInput)

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyPressedEvent: " << (int)m_KeyCode << " (" << m_RepeatCount << " repeats)";
		return ss.str();
	}

private:
	int m_RepeatCount;
};

class KeyReleasedEvent : public KeyEvent
{
public:
	KeyReleasedEvent(int keycode)
		: KeyEvent(keycode)
	{
	}

	EVENT_CLASS_TYPE(EventSource::EventCategoryInput)

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyReleasedEvent: " << (int)m_KeyCode;
		return ss.str();
	}
};

class KeyTypedEvent : public KeyEvent
{
public:
	KeyTypedEvent(char* keycode)
		: KeyEvent(keycode[0]), keys(keycode)
	{
	}

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyTypedEvent: " << (char)m_KeyCode;
		return ss.str();
	}

	EVENT_CLASS_TYPE(EventSource::EventCategoryInput)

	char* GetText()
	{
		return keys;
	}

private:
	char* keys;
};
