#include "shpch.h"
#include "SceneEntity.h"

namespace ShadowEngine::EntitySystem {

	void SceneEntity::TransformChanged(bool self)
	{
		if(!self)
		this->transform.UpdateMatrix();
		
		Entity::TransformChanged(self);
	}

	ShadowEntity::Transform* SceneEntity::GetTransform()
	{
		return &this->transform;
	}

	void SceneEntity::SetParent(rtm_ptr<Entity> e)
	{
		Entity::SetParent(e);

		//transform.parent = e->GetTransform();
	}
}
