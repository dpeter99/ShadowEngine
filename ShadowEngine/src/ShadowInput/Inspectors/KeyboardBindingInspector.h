#pragma once
#include "ShadowInput/IInputBinding.h"
#include "ShadowInput/IShadowAction.h"
#include "ShadowInput/Bindings/KeyboardBinding.h"
#include "Inspector/Inspector.h"
#include "imgui.h"

class KeyboardBindingInspector :
	public Inspector

{
	SHObject_Base(KeyboardBindingInspector)


public:
	void Draw(SHObject& obj)
	{
		auto& keyboard = dynamic_cast<ShadowInput::KeyboardBinding&>(obj);
		ImGui::Text("KeyboardBinding: %c", SDL_GetKeyFromScancode((SDL_Scancode)keyboard.GetKeycode()));

		for (int i = 0; i < keyboard.ModifierCount(); ++i)
		{
			InspectorSystem::DrawSub(keyboard.GetModifier(i));
		}
		
	}
};
