#pragma once
#include "Core/SHObject.h"
#include "EntitySystem/Entity.h"

namespace ShadowEngine::Debug {

	class EntityInspector :
		public ShadowEngine::SHObject
	{
		SHObject_Base(EntityInspector)

	public:
		virtual void Draw(EntitySystem::rtm_ptr<EntitySystem::Entity> & obj) = 0;
	};

}