#pragma once
#include <list>
#include "ShadowModule.h"

class ShadowModuleManager
{
public:
	static ShadowModuleManager* instance;

	std::list<ShadowModule*> modules;

	ShadowModuleManager();
	~ShadowModuleManager();

	void PushModule(ShadowModule* module);

	ShadowModule& GetModule(std::string name);

	void Init();
	void Update();
};
