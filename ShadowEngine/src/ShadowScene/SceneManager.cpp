#include "shpch.h"
#include "SceneManager.h"

SceneManager::SceneManager() : activeScene(std::make_unique<ShadowScene>())
{

}

void SceneManager::Init()
{
	
}

void SceneManager::Update()
{
}

ShadowEngine::Scope<ShadowScene>& SceneManager::GetActiveScene()
{
	return activeScene;
}

void SceneManager::LoadEmptyScene()
{
	if(activeScene != NULL)
	{
		SH_CORE_CRITICAL("Scene wasn't unloaded.");
	}

	activeScene = std::make_unique<ShadowScene>();
}

void SceneManager::LoadScene(ShadowScene* scene)
{
	if (activeScene != NULL)
	{
		//SH_CORE_CRITICAL("Scene wasn't unloaded.");
	}
	
	activeScene.reset(scene);
}
