#pragma once
#include "ShadowModules/ShadowModule.h"
#include "ShadowEvents/IShadowEventListener.h"
#include "ImGui/IShadowImGui.h"

class Debug :
	public ShadowModule,
	public IShadowEventListener,
	public IShadowImGui
{

	void Debug::ActionDebug();

public:

	bool active;

	void Init() override;

	void Update() override {};

	std::string GetName() override { return "Debug"; };

	void OnEvent(ShadowEvent& e) override;

	void OnGui() override;


	Debug();
	virtual ~Debug();
};
