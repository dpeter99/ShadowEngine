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
#include "Util/Utility.h"
#include "ShadowInput/Bindings/Binding1D.h"
#include "ShadowTime.h"
#include "Inspector/Inspector.h"
#include "Inspector/InspectorSystem.h"


Debug::Debug()
{
}

Debug::~Debug()
{
}



void Debug::Init()
{
	ShadowEventSystem::ShadowEventManager::AddNewEventListener(this);
	ImGuiModule::AddGUICall(this);

	//new ShadowInput::ShadowAction<bool>("Test", new ShadowInput::KeyboardBinding("a"));

	active = true;
}

void Debug::OnEvent(ShadowEventSystem::ShadowEvent& e)
{
	//std::cout << e.ToString() << std::endl;
}

void Debug::ActionDebug()
{
	auto evMan = ShadowInput::ShadowActionSystem::_instance;

	ImGui::Begin("Actions", &active, ImGuiWindowFlags_MenuBar);

	for (ShadowInput::IShadowAction* element : evMan->actions)
	{
		if (ImGui::TreeNode(element, element->GetName().c_str())) {

			InspectorSystem::Draw(*element);

			ImGui::TreePop();
		}
		ImGui::Separator();
		
	}

	ImGui::End();
}

void Debug::OnGui()
{
	ImGui::ShowDemoWindow();

	ImGui::Begin("Time", &active, ImGuiWindowFlags_MenuBar);

	ImGui::Text("delta time in ms: %lf", Time::deltaTime_ms);
	ImGui::Text("delta time in s: %lf", Time::deltaTime);
	ImGui::Text("LAST time in: %ld", Time::LAST);

	ImGui::End();

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

