#include "shpch.h"
#include "SceneManager.h"



ShadowScene::SceneManager::SceneManager() : activeScene(std::make_unique<ShadowScene>())
{

}

void ShadowScene::SceneManager::Init()
{
	
}

void ShadowScene::SceneManager::Update()
{
}

ShadowEngine::Scope<ShadowScene::ShadowScene>& ShadowScene::SceneManager::GetActiveScene()
{
	return activeScene;
}

void ShadowScene::SceneManager::LoadEmptyScene()
{
	if(activeScene != NULL)
	{
		SH_CORE_CRITICAL("Scene wasn't unloaded.");
	}

	//activeScene = std::make_unique<ShadowScene>();
}

void ShadowScene::SceneManager::LoadScene(ShadowScene* scene)
{
	if (activeScene != NULL)
	{
		//SH_CORE_CRITICAL("Scene wasn't unloaded.");
	}
	
	activeScene.reset(scene);

	scene->Init();

	SH_CORE_TRACE("SceneLoaded");
}
