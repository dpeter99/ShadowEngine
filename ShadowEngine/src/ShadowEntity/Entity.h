#pragma once

#include <string>
#include <iostream>

#include "EntityBase.h"

class ShadowScene;

namespace ShadowEntity 
{
	class Entity : public SHObject
	{
		SHObject_Base(Entity)
		
	public:

		ShadowEngine::Ref<ShadowScene> scene;


	public:
		virtual Entity* Create();

		virtual void Start();

		virtual void Update();

		virtual void LateUpdate();

		virtual void Render();

		virtual  void LateRender();

	public:
		void SetScene(ShadowScene* scene);

		friend std::ostream& operator<<(std::ostream& os, const Entity& dt);
	};
}