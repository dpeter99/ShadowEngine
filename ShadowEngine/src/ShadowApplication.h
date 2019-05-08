#pragma once
#include "ShadowModules/ShadowModuleManager.h"
#include "ShadowAsset/AssetManager.h"
#include "ShadowWindow.h"

class ShadowApplication
{
	static ShadowApplication* instance;

	ShadowWindow* window_;

	ShadowModuleManager moduleManager;

	AssetManager asset;

	bool running = true;

public:
	ShadowApplication();
	virtual ~ShadowApplication();

	static ShadowApplication& Get() { return *instance; };

	ShadowWindow& GetWindow() const { return *window_; };
	void SetWindow(ShadowWindow* w) { window_ = w; }

	ShadowModuleManager& GetModuleManager() { return moduleManager; };

	void Init();
	void Start();
};
