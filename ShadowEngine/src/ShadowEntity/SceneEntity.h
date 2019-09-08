#pragma once

#include "ShadowEntity/Entity.h"
#include "ShadowEntity/Transform.h"
#include <glm/glm.hpp>

#define BIND_EVENT_FN(x, ...) std::bind(&x, this, __VA_ARGS__)

namespace ShadowEntity {

	class SceneEntity :
		public Entity
	{
		SHObject_Base(SceneEntity)

			void virtual TransformChanged() = 0;


	public:
		SceneEntity()
		{
			transform.transformChanged += std::bind(&SceneEntity::TransformChanged, this);
		};

		Transform transform;
	};

}