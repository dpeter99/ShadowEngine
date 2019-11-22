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
		public Entity
	{
		SHObject_Base(SceneEntity);

		Entity_Base_NoCtor(SceneEntity, Entity);
		
	public:

	public:
		ShadowEntity::Transform transform;

		SceneEntity() :Entity() { transform.AssignEntity(this); }

		SceneEntity(EntitySystem::Scene* scene) : Entity(scene)
		{
			transform.transformChanged += std::bind(&SceneEntity::TransformChanged, this, true);
			transform.AssignEntity(this);
		};

		virtual void TransformChanged(bool self) override;

		virtual ShadowEntity::Transform* GetTransform();
		
		void SetParent(rtm_ptr<Entity> e) override;
		
		
	};

}