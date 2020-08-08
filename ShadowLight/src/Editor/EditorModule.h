#pragma once
#include "EditorWindow.h"
#include "EntitySystem/EntitySystem.h"
#include "ImGui/IShadowImGui.h"
#include "ShadowEvents/IShadowEventListener.h"
#include "ShadowModules/ShadowModule.h"



namespace ShadowLight::Editor {

	class EditorModule :
		public ShadowEngine::ShadowModule,
		public ShadowEngine::EventSystem::IShadowEventListener,
		public ShadowEngine::DebugGui::IShadowImGui
	{
		ShadowEngine::EntitySystem::rtm_ptr<ShadowEngine::EntitySystem::Entity> selected_ent;
		ShadowEngine::EntitySystem::rtm_ptr<ShadowEngine::EntitySystem::Entity> selected_inspector;


		std::vector<EditorWindow*> windows;

		
		void ActionDebug();
		void DebugHierarchy();
		void Inspector();

		

	public:

		bool active;

		void PreInit() override;;
		void Init() override;
		void Update() override {};
		void Render() override {};
		void LateRender() override {};

		std::string GetName() override { return "Editor Module"; };

		void OnEvent(ShadowEngine::EventSystem::ShadowEvent& e) override;

		void OnGui() override;


		EditorModule();
		virtual ~EditorModule();
	};
}
