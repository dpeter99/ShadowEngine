#pragma once
#include "ShadowModules/ShadowModule.h"
#include "ShadowEvents/IShadowEventListener.h"
#include <list>
#include "IShadowImGui.h"

class ImGuiModule :
	public ShadowModule, public ShadowEventSystem::IShadowEventListener
{
	static ImGuiModule* instance;

	std::list<IShadowImGui*> guiCalls;

public:

	void Init() override;

	void Update() override;

	void OnEvent(ShadowEventSystem::ShadowEvent& e) override;

	std::string GetName() override { return "ImGuiModule"; };

	static void AddGUICall(IShadowImGui* g);

	ImGuiModule();
	~ImGuiModule();
};
