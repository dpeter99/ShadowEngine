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
	SH_ASSERT(false, "Can't find the module");
	//return NULL;
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

void ShadowModuleManager::LateRender()
{
	for (auto module : modules)
	{
		module->LateRender();
	}
}

void ShadowModuleManager::Render()
{
	for (auto module : modules)
	{
		module->Render();
	}
}
