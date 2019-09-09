#include "shpch.h"
#include "SceneManager.h"

void SceneManager::Init()
{
	
}

void SceneManager::Update()
{
}

void SceneManager::LoadEmptyScene()
{
	if(activeScene != NULL)
	{
		SH_CORE_CRITICAL("Scene wasn't unloaded.");
	}

	activeScene = new ShadowScene();
}

void SceneManager::LoadScene(ShadowScene* scene)
{
	if (activeScene != NULL)
	{
		SH_CORE_CRITICAL("Scene wasn't unloaded.");
	}
	
	activeScene = scene;
}
