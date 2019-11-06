#pragma once

#include "ShadowEntity/Entity.h"
#include "ShadowEntity/Transform.h"
#include <glm/glm.hpp>

#define BIND_EVENT_FN(x, ...) std::bind(&x, this, __VA_ARGS__)

namespace ShadowEngine::ShadowEntity {

	/// <summary>
	/// Entitys that have a world positon
	/// </summary>
	class SceneEntity :
		public Entity
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
		Transform transform;

		SceneEntity():Entity(){}

		SceneEntity(Scene::ShadowScene* scene) : Entity(scene)
		{
			transform.transformChanged += std::bind(&SceneEntity::TransformChanged, this);
		};

		
	};

}