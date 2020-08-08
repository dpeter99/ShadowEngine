#pragma once
#include "ShadowModules/ShadowModule.h"
#include "ShadowEvents/IShadowEventListener.h"
#include <list>
#include "IShadowImGui.h"

namespace ShadowEngine::DebugGui {

	class ImGuiModule :
		public ShadowEngine::ShadowModule, public EventSystem::IShadowEventListener
	{
		static ImGuiModule* instance;

		std::list<IShadowImGui*> guiCalls;


	public:

		void PreInit() override {};
		void Init() override;
		void Update() override {};
		void Render() override {};
		void LateRender() override;
		void AfterFrameEnd() override;

		void OnEvent(EventSystem::ShadowEvent& e) override;


		static void StartFrame();
		static void OtherWindows();

		
		std::string GetName() override { return "ImGuiModule"; };

		static void AddGUICall(IShadowImGui* g);

		ImGuiModule();
		~ImGuiModule();
		
	};
}