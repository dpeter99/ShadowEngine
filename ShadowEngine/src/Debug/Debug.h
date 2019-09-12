#pragma once
#include "ShadowModules/ShadowModule.h"
#include "ShadowEvents/IShadowEventListener.h"
#include "ImGui/IShadowImGui.h"
#include <map>

class Debug :
	public ShadowEngine::ShadowModule,
	public ShadowEventSystem::IShadowEventListener,
	public IShadowImGui
{

	void Debug::ActionDebug();

public:

	bool active;

	void Init() override;
	void Update() override {};
	void Render() override {};
	void LateRender() override {};

	std::string GetName() override { return "Debug"; };

	void OnEvent(ShadowEventSystem::ShadowEvent& e) override;

	void OnGui() override;


	Debug();
	virtual ~Debug();
};
