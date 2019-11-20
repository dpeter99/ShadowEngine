#include "shpch.h"
#include "SceneManager.h"

namespace ShadowEngine::EntitySystem {

	SceneManager::SceneManager() : activeScene(std::make_unique<Scene>())
	{

	}

	void SceneManager::Init()
	{

	}

	void SceneManager::Update()
	{
	}

	ShadowEngine::Scope<Scene>& EntitySystem::SceneManager::GetActiveScene()
	{
		return activeScene;
	}

	void EntitySystem::SceneManager::LoadEmptyScene()
	{
		if (activeScene != NULL)
		{
			SH_CORE_CRITICAL("Scene wasn't unloaded.");
		}

		//activeScene = std::make_unique<ShadowScene>();
	}

	void SceneManager::LoadScene(Scene* scene)
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