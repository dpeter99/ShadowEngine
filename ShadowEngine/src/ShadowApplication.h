#pragma once
#include "ShadowModules/ShadowModuleManager.h"
#include "ShadowAsset/AssetManager.h"

class ShadowApplication
{
	static ShadowApplication* instance;

	ShadowModuleManager moduleManager;

	AssetManager asset;

	bool running = true;

public:
	ShadowApplication();
	virtual ~ShadowApplication();

	static ShadowApplication& Get() { return  *instance; };

	void Init();
	void Start();
};

