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

void Debug::OnGui()
{
	// Create a window called "My First Tool", with a menu bar.
	ImGui::Begin("Active Modules", &active, ImGuiWindowFlags_MenuBar);

	ShadowModuleManager* m = ShadowModuleManager::instance;

	//ImGui::BeginChild("Scrolling");
	ImGui::TextColored(ImVec4(1, 1, 0.4, 1), "Active Modules:");
	for (auto module : m->modules)
	{
		ImGui::Text("%s",module->GetName().c_str());
	}
	//ImGui::EndChild();

	
	
	ImGui::End();

}

Debug::Debug()
{
}


Debug::~Debug()
{
}
