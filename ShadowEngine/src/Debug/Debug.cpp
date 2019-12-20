#include "shpch.h"

#include "Debug.h"
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
#include "EntitySystem/EntitySystem.h"
#include <Core\ShadowApplication.h>

namespace ShadowEngine::Debug {

	DebugModule::DebugModule() : active(false)
	{
	}

	DebugModule::~DebugModule()
	{
	}



	void DebugModule::Init()
	{
		EventSystem::ShadowEventManager::AddNewEventListener(this);
		DebugGui::ImGuiModule::AddGUICall(this);

		//new ShadowInput::ShadowAction<bool>("Test", new ShadowInput::KeyboardBinding("a"));

		active = true;
	}

	void DebugModule::OnEvent(EventSystem::ShadowEvent& e)
	{
		//std::cout << e.ToString() << std::endl;
	}

	void DebugModule::ActionDebug()
	{
		auto evMan = InputSystem::ShadowActionSystem::_instance;

		ImGui::Begin("Actions", &active, ImGuiWindowFlags_MenuBar);

		for (InputSystem::IShadowAction* element : evMan->actions)
		{
			if (ImGui::TreeNode(element, element->GetName().c_str())) {

				InspectorSystem::InspectorSystem::Draw(*element);

				ImGui::TreePop();
			}
			ImGui::Separator();

		}

		ImGui::End();
	}

	void DebugModule::DebugHierarchy()
	{
		static bool shown;

		auto* scenemg = ShadowEngine::ShadowApplication::Get().GetModuleManager().GetModuleByType<EntitySystem::EntitySystem>();
		
		ImGui::Begin("Hierarchy", &shown, ImGuiWindowFlags_MenuBar);

		auto& scene = scenemg->GetActiveScene();
		
		if( ImGui::TreeNode((void*)&scene,scene->Type().c_str()))
		{
			for each (auto& entity in scene->m_entities)
			{
				if (ImGui::TreeNode((void*)&entity, entity->name.c_str()))
				{
					
					ImGui::TreePop();
				}
			}

			ImGui::TreePop();
		}


		
		
		ImGui::End();
	}

	void DebugModule::OnGui()
	{
		//ImGui::ShowDemoWindow();

		ImGui::Begin("Time", &active, ImGuiWindowFlags_MenuBar);

		ImGui::Text("delta time in ms: %lf", Time::deltaTime_ms);
		ImGui::Text("delta time in s: %lf", Time::deltaTime);
		ImGui::Text("LAST time in: %ld", Time::LAST);

		ImGui::End();

		ImGui::Begin("Active Modules", &active, ImGuiWindowFlags_MenuBar);

		ShadowEngine::ShadowModuleManager* m = ShadowEngine::ShadowModuleManager::instance;



		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.4f, 1.0f), "Active Modules:");
		for (auto& module : m->modules)
		{
			ImGui::Text("%s", module->GetName().c_str());
		}


		ImGui::End();

		ActionDebug();

		DebugHierarchy();
	}

}
