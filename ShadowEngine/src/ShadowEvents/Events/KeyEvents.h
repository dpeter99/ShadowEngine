#pragma once
#include  "shpch.h"
#include "ShadowEvents/ShadowEvent.h"
#include <SDL.h>

namespace ShadowEngine::EventSystem::Events {

	class KeyEvent : public ShadowEvent
	{
		SHObject_Base(KeyEvent)

	public:
		int GetKeyCode() const { return m_KeyCode; }

	protected:
		KeyEvent(int keycode, SDL_Event* ev)
			: m_KeyCode(keycode), ShadowEvent(ev)
		{
		}

		int m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent
	{
		SHObject_Base(KeyPressedEvent)

	public:
		KeyPressedEvent(int keycode, int repeatCount, SDL_Event* ev)
			: KeyEvent(keycode, ev), m_RepeatCount(repeatCount)
		{
		}

		int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << "\t" << (char)SDL_GetKeyFromScancode((SDL_Scancode)m_KeyCode) << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

	private:
		int m_RepeatCount;
	};

	class KeyReleasedEvent : public KeyEvent
	{
		SHObject_Base(KeyReleasedEvent)

	public:
		KeyReleasedEvent(int keycode, SDL_Event* ev)
			: KeyEvent(keycode, ev)
		{
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << "\t" << (char)SDL_GetKeyFromScancode((SDL_Scancode)m_KeyCode);
			return ss.str();
		}
	};

	class KeyTypedEvent : public KeyEvent
	{
		SHObject_Base(KeyTypedEvent)

	public:
		KeyTypedEvent(char* keycode, SDL_Event* ev)
			: KeyEvent(keycode[0],ev), keys(keycode)
		{
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << (char)m_KeyCode;
			return ss.str();
		}

		char* GetText()
		{
			return keys;
		}

	private:
		char* keys;
	};

}