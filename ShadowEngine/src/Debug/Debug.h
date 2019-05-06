#pragma once
#include "ShadowModules/ShadowModule.h"
#include "ShadowEvents/IShadowEventListener.h"
#include "ImGui/IShadowImGui.h"
#include "Inspector.h"
#include <map>

class Debug :
	public ShadowModule,
	public IShadowEventListener,
	public IShadowImGui
{

	std::map<std::string, Inspector*> inspectors;

	void Debug::ActionDebug();

public:

	bool active;

	void Init() override;

	void Update() override {};

	std::string GetName() override { return "Debug"; };

	void OnEvent(ShadowEvent& e) override;

	void OnGui() override;


	//Inspector Stuff
	void AddInspector(std::string name, Inspector* inspector);

	Debug();
	virtual ~Debug();
};
