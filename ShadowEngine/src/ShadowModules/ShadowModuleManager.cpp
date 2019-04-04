#include "ShadowModuleManager.h"

ShadowModuleManager* ShadowModuleManager::instance = nullptr;

ShadowModuleManager::ShadowModuleManager()
{
	if (instance != nullptr)
	{
		//ERROR
	}
	instance = this;
}

ShadowModuleManager::~ShadowModuleManager()
{
}

void ShadowModuleManager::PushModule(ShadowModule* module)
{
	modules.emplace_back(module);
}

void ShadowModuleManager::Init()
{
	for (auto module : modules)
	{
		module->Init();
	}
}
