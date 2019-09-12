#include "shpch.h"

#include "ShadowModuleManager.h"

ShadowEngine::ShadowModuleManager* ShadowEngine::ShadowModuleManager::instance = nullptr;

ShadowEngine::ShadowModuleManager::ShadowModuleManager()
{
	if (instance != nullptr)
	{
		//ERROR
	}
	instance = this;
}

ShadowEngine::ShadowModuleManager::~ShadowModuleManager()
{
}

void ShadowEngine::ShadowModuleManager::PushModule(ShadowModule* module)
{
	modules.emplace_back(module);
}

ShadowEngine::ShadowModule& ShadowEngine::ShadowModuleManager::GetModule(std::string name)
{
	for (auto& module : modules)
	{
		if (module->GetName() == name)
			return *module;
	}
	SH_ASSERT(false, "Can't find the module");
	//return NULL;
}

void ShadowEngine::ShadowModuleManager::Init()
{
	for (auto& module : modules)
	{
		module->Init();
	}
}

void ShadowEngine::ShadowModuleManager::Update()
{
	for (auto& module : modules)
	{
		module->Update();
	}
}

void ShadowEngine::ShadowModuleManager::LateRender()
{
	for (auto& module : modules)
	{
		module->LateRender();
	}
}

void ShadowEngine::ShadowModuleManager::Render()
{
	for (auto& module : modules)
	{
		module->Render();
	}
}
