#pragma once
#include "ShadowModules/ShadowModule.h"
#include "ShadowEvents/IShadowEventListener.h"
#include "ImGui/IShadowImGui.h"
#include <map>

namespace ShadowEngine::Debug {

	class DebugModule :
		public ShadowModule,
		public EventSystem::IShadowEventListener,
		public DebugGui::IShadowImGui
	{

		void DebugModule::ActionDebug();

	public:

		bool active;

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