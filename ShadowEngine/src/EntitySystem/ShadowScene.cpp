#include "shpch.h"
#include "ShadowScene.h"

namespace ShadowEngine::EntitySystem {

	void EntitySystem::Scene::Start()
	{
		for (auto& entity : m_entities)
		{
			entity->Start();
		}
	}

	void Scene::Update()
	{
		for (auto& entity : m_entities)
		{
			//entity->Update(dt);
		}
	}

	void Scene::LateUpdate()
	{
		for (auto& entity : m_entities)
		{
			entity->LateUpdate();
		}
	}

	void Scene::Render()
	{
		for (auto& entity : m_entities)
		{
			entity->Render();
		}
	}

	void Scene::LateRender()
	{
		for (auto& entity : m_entities)
		{
			entity->LateRender();
		}
	}

	void Scene::Init() {

		for (auto& entity : m_entities)
		{
			entity->Init();
		}
	}
}