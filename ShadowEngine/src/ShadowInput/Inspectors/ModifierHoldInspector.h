#pragma once
#include "ShadowInput/Modifiers/ModifierHold.h"
#include "Inspector/Inspector.h"
#include "imgui.h"

class ModifierHoldInspector : public Inspector
{
public:
	void Draw(SHObject& obj) override
	{
		auto& hold = dynamic_cast<ShadowInput::ModifierHold&>(obj);

		ImGui::AlignTextToFramePadding();
		ImGui::Text("ModifierHold: %.2f/%.2f", hold.GetWaitTime(), hold.GetDeltaTime());
		ImGui::SameLine(0.0f,10.0f); ImGui::ProgressBar(hold.GetDeltaTime() / hold.GetWaitTime());
	}
};
