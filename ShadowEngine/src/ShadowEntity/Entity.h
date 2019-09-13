#pragma once

#include <string>
#include <iostream>

//#include "ShadowScene/ShadowScene.h"

#include "EntityBase.h"

namespace ShadowEngine::Scene
{
	class ShadowScene;
}

namespace ShadowEngine::ShadowEntity
{

	

	class Entity : public SHObject
	{
		SHObject_Base(Entity)
		
	public:

		Scene::ShadowScene* scene;


	public:
		Entity();

		Entity(Scene::ShadowScene* scene);

		virtual Entity* Create(Scene::ShadowScene* scene);

		virtual  void Init();
		
		virtual void Start();

		virtual void Update();

		virtual void LateUpdate();

		virtual void Render();

		virtual  void LateRender();

	public:
		void SetScene(Scene::ShadowScene* se);

		friend std::ostream& operator<<(std::ostream& os, const Entity& dt);
	};
}
