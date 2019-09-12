#pragma once

#include <string>
#include <iostream>

#include "EntityBase.h"



namespace ShadowEntity 
{
	class ShadowScene;

	class Entity : public ShadowEngine::SHObject
	{
		SHObject_Base(Entity)
		
	public:

		ShadowScene* scene;


	public:
		Entity();

		Entity(ShadowScene* scene);

		virtual Entity* Create(ShadowScene* scene);

		virtual  void Init();
		
		virtual void Start();

		virtual void Update();

		virtual void LateUpdate();

		virtual void Render();

		virtual  void LateRender();

	public:
		void SetScene(ShadowScene* se);

		friend std::ostream& operator<<(std::ostream& os, const Entity& dt);
	};
}