#include "shpch.h"

#include "Debug.h"
#include <iostream>
#include "ShadowEvents/ShadowEventManager.h"
#include "ImGui/ImGuiModule.h"
#include "imgui.h"
#include "ShadowModules/ShadowModuleManager.h"
#include "ShadowInput/ShadowAction.h"
#include "ShadowInput/Bindings/KeyboardBinding.h"
#include "ShadowInput/Modifiers/ModifierHold.h"
#include "Utility.h"


void Debug::Init()
{
	ShadowEventManager::AddNewEventListener(this);
	ImGuiModule::AddGUICall(this);

	//new ShadowInput::ShadowAction<bool>("Test", new ShadowInput::KeyboardBinding("a"));

	active = true;
}

void Debug::OnEvent(ShadowEvent& e)
{
	std::cout << e.ToString() << std::endl;
}

void Debug::ActionDebug()
{
	auto evMan = ShadowInput::ShadowActionSystem::_instance;

	ImGui::Begin("Actions", &active, ImGuiWindowFlags_MenuBar);

	for (auto element : evMan->actions)
	{
		bool actionActive = element->GetPerformed();

		ImGui::Checkbox("", &actionActive);
		ImGui::SameLine(); ImGui::Text("%s \t %d", element->GetName().c_str(), element->GetState());
		
		

		auto* binding = &(element->GetBinding());

		ShadowInput::KeyboardBinding* keyboard;
		if (is(*binding, &keyboard))
		{
			ImGui::Text("KeyboardBinding: %c", keyboard->GetKeycode());
		}

		if (binding->ModifierCount() > 0) {
			auto* mod = &(binding->GetModifier(0));

			ShadowInput::ModifierHold* hold;
			if (is(*mod, &hold))
			{
				ImGui::Text("ModifierHold: %c", hold->GetWaitTime());
				ImGui::ProgressBar(hold->GetDeltaTime() / hold->GetWaitTime());
			}
		}

		ImGui::Separator();
	}

	ImGui::End();
}

void Debug::OnGui()
{
	ImGui::ShowDemoWindow();

	// Create a window called "My First Tool", with a menu bar.
	ImGui::Begin("Active Modules", &active, ImGuiWindowFlags_MenuBar);

	ShadowModuleManager* m = ShadowModuleManager::instance;

	//ImGui::BeginChild("Scrolling");
	ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.4f, 1.0f), "Active Modules:");
	for (auto module : m->modules)
	{
		ImGui::Text("%s", module->GetName().c_str());
	}
	//ImGui::EndChild();

	ImGui::End();

	ActionDebug();
}

Debug::Debug()
{
}


Debug::~Debug()
{
}
