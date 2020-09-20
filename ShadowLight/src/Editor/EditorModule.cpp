#include "shpch.h"
#include "EditorModule.h"



#include "Debug/Debug.h"
#include "ImGui/ImGuiModule.h"
#include "imgui.h"
#include "ShadowTime.h"
#include "AssetsWindow/AssetsWindow.h"
#include "Core/ShadowApplication.h"
#include "ImGui/IconsFontAwesome5.h"
#include "Inspector/InspectorSystem.h"
#include "RendererInfo/RendererInfo.h"
#include "ShadowEvents/ShadowEventManager.h"
#include "ShadowInput/ShadowActionSystem.h"

namespace ShadowLight::Editor {

	EditorModule::EditorModule() : active(false)
	{
	}

	EditorModule::~EditorModule()
	{
	}

	void EditorModule::PreInit()
	{
		windows.push_back(new AssetsWindow());
		windows.push_back(new RendererInfo());
	}

	void EditorModule::Init()
	{
		ShadowEngine::EventSystem::ShadowEventManager::AddNewEventListener(this);
		if(ShadowEngine::ShadowApplication::Get().GetModuleManager().GetModuleByType<ShadowEngine::DebugGui::ImGuiModule>() != nullptr)
			ShadowEngine::DebugGui::ImGuiModule::AddGUICall(this);

		//new ShadowInput::ShadowAction<bool>("Test", new ShadowInput::KeyboardBinding("a"));

		active = true;


		RegisterEntityInspectors();
	}

	void EditorModule::OnEvent(ShadowEngine::EventSystem::ShadowEvent& e)
	{
		//std::cout << e.ToString() << std::endl;
	}

	void EditorModule::ActionDebug()
	{
		auto evMan = ShadowEngine::InputSystem::ShadowActionSystem::_instance;

		ImGui::Begin("Actions", &active, ImGuiWindowFlags_MenuBar);

		for (ShadowEngine::InputSystem::IShadowAction* element : evMan->actions)
		{
			if (ImGui::TreeNode(element, element->GetName().c_str())) {
				ShadowEngine::Debug::InspectorSystem::InspectorSystem::Draw(*element);

				ImGui::TreePop();
			}
			ImGui::Separator();

		}

		ImGui::End();
	}

	void EditorModule::DebugHierarchy()
	{
		static bool shown;

		auto* scenemg = ShadowEngine::ShadowApplication::Get().GetModuleManager().GetModuleByType<ShadowEngine::EntitySystem::EntitySystem>();

		ImGui::Begin("Hierarchy", &shown, ImGuiWindowFlags_MenuBar);

		auto& scene = scenemg->GetActiveScene();

		if (ImGui::TreeNode((void*)&scene, scene->Type().c_str()))
		{
			for each (auto & entity in scene->m_entities)
			{

				ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow;
				if (selected_ent == entity)
					node_flags |= ImGuiTreeNodeFlags_Selected;

				if (ImGui::TreeNodeEx((std::string(ICON_FA_CUBE) + " " + entity->name).c_str(), node_flags))
				{


					ImGui::TreePop();
				}

				if (ImGui::IsItemClicked()) {
					selected_ent = entity;
					selected_inspector = entity;
				}

			}

			ImGui::TreePop();
		}

		ImGui::End();



	}


	template<class T>
	ImGuiTreeNodeFlags treeSelectableFlags(T a, T b) {
		ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow;
		if (a == b)
			node_flags |= ImGuiTreeNodeFlags_Selected;

		return node_flags;
	}

	void EditorModule::Inspector() {
		static bool shown = true;

		ImGui::Begin("Inspector", &shown, ImGuiWindowFlags_None);

		if (selected_ent) {

			std::string title = selected_ent->name;
			title += " (" + selected_ent->Type() + ")";
			ImGui::Text(title.c_str(), "");

			ImGui::Separator();

			bool top_open = ImGui::TreeNodeEx(selected_ent->name.c_str(), treeSelectableFlags(selected_ent, selected_inspector));
			if (ImGui::IsItemClicked())
				selected_inspector = selected_ent;
			if (top_open)
			{
				for each (auto & entity in selected_ent->internalHierarchy)
				{

					bool open = ImGui::TreeNodeEx(entity->name.c_str(), treeSelectableFlags(entity, selected_inspector));

					if (ImGui::IsItemClicked())
						selected_inspector = entity;

					if (open) {
						ImGui::TreePop();
					}

				}

				ImGui::TreePop();
			}

			ImGui::Separator();

			if (selected_inspector) {
				ShadowEngine::Debug::InspectorSystem::DrawEntityInspector(selected_inspector);
			}
		}

		ImGui::End();
	}

	void DrawDefaultInspector(ShadowEngine::EntitySystem::rtm_ptr<ShadowEngine::EntitySystem::Entity> entity) {
		ShadowEngine::Debug::InspectorSystem::DrawEntityInspector(entity);
	}

	void EditorModule::OnGui()
	{
		ImGui::ShowDemoWindow();

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

		Inspector();

		for each (Editor::EditorWindow* window in windows)
		{
			window->Draw();
		}
	}
	
}
