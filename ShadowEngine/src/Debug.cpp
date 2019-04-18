#include "Debug.h"
#include <iostream>
#include "ShadowEvents/ShadowEventManager.h"
#include "ImGui/ImGuiModule.h"
#include "imgui.h"
#include "ShadowModules/ShadowModuleManager.h"
#include "ShadowInput/ShadowAction.h"
#include "ShadowInput/Bindings/KeyboardBinding.h"


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
		ImGui::Text("%s \t %d", element->GetName().c_str(), element->GetState());

	}

	ImGui::End();
}

void Debug::OnGui()
{
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
