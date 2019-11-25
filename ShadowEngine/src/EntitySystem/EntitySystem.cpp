#include "shpch.h"
#include "EntitySystem.h"
#include <ShadowTime.h>

namespace ShadowEngine::EntitySystem {

	EntitySystem::EntitySystem() : activeScene(std::make_unique<Scene>())
	{
		entityMgr = new EntityManager();
	}

	void EntitySystem::Init()
	{
		
	}

	void EntitySystem::Update()
	{
		auto dt = Time::deltaTime_ms;

		entityMgr->UpdateEntities(dt);
	}

	ShadowEngine::Scope<Scene>& EntitySystem::EntitySystem::GetActiveScene()
	{
		return activeScene;
	}

	void EntitySystem::EntitySystem::LoadEmptyScene()
	{
		if (activeScene != NULL)
		{
			SH_CORE_CRITICAL("Scene wasn't unloaded.");
		}

		//activeScene = std::make_unique<ShadowScene>();
	}

	void EntitySystem::LoadScene(Scene* scene)
	{
		if (activeScene != NULL)
		{
			//SH_CORE_CRITICAL("Scene wasn't unloaded.");
		}

		activeScene.reset(scene);

		scene->Init();

		SH_CORE_TRACE("SceneLoaded");
	}

}