#pragma once

#include <string>
#include <iostream>

#include "EntityBase.h"

namespace ShadowEntity 
{
	class Entity : public SHObject
	{
		SHObject_Base(Entity)
		
	public:

		static std::string id;

		//static std::string Register();
	public:
		virtual Entity* Create();

		virtual void Start();

		virtual void Update();

		virtual void LateUpdate();

		virtual void Draw();

		friend std::ostream& operator<<(std::ostream& os, const Entity& dt);
	};
}