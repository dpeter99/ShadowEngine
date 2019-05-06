#include "shpch.h"

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

ShadowModule& ShadowModuleManager::GetModule(std::string name)
{
	for (auto module : modules)
	{
		if (module->GetName() == name)
			return *module;
	}
}

void ShadowModuleManager::Init()
{
	for (auto module : modules)
	{
		module->Init();
	}
}

void ShadowModuleManager::Update()
{
	for (auto module : modules)
	{
		module->Update();
	}
}
