#pragma once
#include "ShadowModules/ShadowModule.h"
#include "ShadowEvents/IShadowEventListener.h"
#include "EntitySystem/Entity.h"
#include "ImGui/IShadowImGui.h"
#include <map>

void RegisterEntityInspectors();

namespace ShadowEngine::Debug {

	class DebugModule :
		public ShadowModule,
		public EventSystem::IShadowEventListener,
		public DebugGui::IShadowImGui
	{

		EntitySystem::rtm_ptr<EntitySystem::Entity> selected_ent;
		EntitySystem::rtm_ptr<EntitySystem::Entity> selected_inspector;

		void DebugModule::ActionDebug();

		void DebugHierarchy();
		void Inspector();

		

	public:

		bool active;

		void PreInit() override {};
		void Init() override;
		void Update() override {};
		void Render() override {};
		void LateRender() override {};

		std::string GetName() override { return "Debug"; };

		void OnEvent(EventSystem::ShadowEvent& e) override;

		void OnGui() override;


		DebugModule();
		virtual ~DebugModule();
	};
}