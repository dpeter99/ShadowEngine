#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "Util/Callback.h"
#include "EntitySystem/Entity.h"


namespace ShadowEngine::EntitySystem
{
	class SceneEntity;
}

namespace ShadowEngine::ShadowEntity {

	class Transform
	{
	public:
		Transform();
		Transform(glm::vec3 pos);
		Transform(glm::vec3 pos, glm::vec3 size);
		Transform(glm::vec3 pos, glm::vec3 size, glm::quat rotation);

		glm::vec3 GetPosition() { return position; }
		void SetPosition(glm::vec3 val);;

		glm::vec3 GetScale() { return scale; };
		void SetScale(glm::vec3 val) { scale = val; UpdateMatrix(); transformChanged(); };

		glm::quat GetRotation() { return rot; };
		void SetRotation(glm::quat val) { rot = val; UpdateMatrix(); transformChanged(); };

		glm::mat4 GetTransformMatrix() { return mat; };
		glm::mat4 GetWorldTransformMatrix() { return w_mat; };

		void AssignEntity(EntitySystem::Entity* e) { entity = e; }
		
		Callback [[DEPRECATED]] transformChanged;

		EntitySystem::rtm_ptr<EntitySystem::Entity> entity;
		
		//Transform* parent = nullptr;

		void UpdateMatrix();
		void UpdateLocalMatrix();
		void UpdateWorldMatrix();
	private:
		

		glm::vec3 position;
		glm::vec3 scale;
		glm::quat rot;

		glm::vec3 w_position;
		glm::vec3 w_scale;
		glm::quat w_rot;
		
		glm::mat4 mat;

		glm::mat4 w_mat;
	};

}
