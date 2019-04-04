#pragma once
#include "ShadowModules/ShadowModuleManager.h"
#include "ShadowAsset/AssetManager.h"

class ShadowApplication
{

	ShadowModuleManager moduleManager;

	AssetManager asset;

	bool running = true;

public:
	ShadowApplication();
	virtual ~ShadowApplication();

	void Init();
	void Start();
};

