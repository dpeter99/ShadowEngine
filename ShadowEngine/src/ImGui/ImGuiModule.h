#pragma once
#include "ShadowModules/ShadowModule.h"

class ImGuiModule :
	public ShadowModule
{
public:

	void Init() override;

	void Update() override;

	ImGuiModule();
	~ImGuiModule();
};

