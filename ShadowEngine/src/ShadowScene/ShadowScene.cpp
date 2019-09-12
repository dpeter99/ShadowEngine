#include "shpch.h"
#include "ShadowScene.h"

void ShadowScene::Start()
{
	for(auto& entity: entities_)
	{
		entity->Start();
	}
}

void ShadowScene::Update()
{
	for (auto& entity : entities_)
	{
		entity->Update();
	}
}

void ShadowScene::LateUpdate()
{
	for (auto& entity : entities_)
	{
		entity->LateUpdate();
	}
}

void ShadowScene::Render()
{
	for (auto& entity : entities_)
	{
		entity->Render();
	}
}

void ShadowScene::LateRender()
{
	for (auto& entity : entities_)
	{
		entity->LateRender();
	}
}

void ShadowScene::Init() {

	for (auto& entity : entities_)
	{
		entity->Init();
	}
}