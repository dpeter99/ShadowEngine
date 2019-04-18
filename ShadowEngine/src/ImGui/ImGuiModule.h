#pragma once
#include "ShadowModules/ShadowModule.h"
#include "ShadowEvents/IShadowEventListener.h"
#include <list>
#include "IShadowImGui.h"

class ImGuiModule :
	public ShadowModule, public IShadowEventListener
{
	static ImGuiModule* instance;

	std::list<IShadowImGui*> guiCalls;

public:

	void Init() override;

	void Update() override;

	void OnEvent(ShadowEvent& e) override;

	std::string GetName() override { return "ImGuiModule"; };

	static void AddGUICall(IShadowImGui* g);

	ImGuiModule();
	~ImGuiModule();
};
