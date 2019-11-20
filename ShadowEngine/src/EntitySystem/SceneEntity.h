#pragma once


#include <glm/glm.hpp>
#include "Entity.h"
#include "ShadowMath/Transform.h"
#include <EntitySystem\EntityBase.h>

#define BIND_EVENT_FN(x, ...) std::bind(&x, this, __VA_ARGS__)

namespace ShadowEngine::EntitySystem {

	/// <summary>
	/// Entitys that have a world positon
	/// </summary>
	class SceneEntity :
		public EntitySystem::Entity
	{
		SHObject_Base(SceneEntity);

		Entity_Base_NoCtor(SceneEntity, Entity);
		
	protected:
		void virtual TransformChanged() {};

		/**
		 * \brief the internal hierarchy of this Entity
		*/
		std::vector<Entity> internalHierarchy;

		std::vector<Entity> hierarchy;
	public:
		ShadowEntity::Transform transform;

		SceneEntity():Entity(){}

		SceneEntity(EntitySystem::Scene* scene) : Entity(scene)
		{
			transform.transformChanged += std::bind(&SceneEntity::TransformChanged, this);
		};

		
	};

}