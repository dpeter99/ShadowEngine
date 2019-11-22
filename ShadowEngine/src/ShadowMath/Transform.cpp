#include "shpch.h"
#include "Transform.h"
#include "EntitySystem/Entity.h"


#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "EntitySystem/SceneEntity.h"

namespace ShadowEngine::ShadowEntity {

	Transform::Transform()
	{
		position = glm::vec3(0, 0, 0);
		scale = glm::vec3(1, 1, 1);
		rot = glm::quat({0,0,0});

		UpdateMatrix();
	}

	Transform::Transform(glm::vec3 pos) : position(pos)
	{
		scale = glm::vec3(1, 1, 1);
		rot = glm::quat({ 0,0,0 });
		UpdateMatrix();
	}

	Transform::Transform(glm::vec3 pos, glm::vec3 size) :position(pos), scale(size)
	{
		rot = glm::quat({ 0,0,0 });

		UpdateMatrix();
	}

	Transform::Transform(glm::vec3 pos, glm::vec3 size, glm::quat rotation) :position(pos), scale(size), rot(rotation)
	{

		UpdateMatrix();
	}

	void Transform::SetPosition(glm::vec3 val)
	{
		position = val;

		if (this->entity->parent)
			w_position = this->entity->parent->GetTransform()->GetPosition() + position;
		else
			w_position = position;		
		
		UpdateMatrix();
		//transformChanged();
		if(entity)
		entity->TransformChanged(true);
	}

	void Transform::UpdateMatrix()
	{
		UpdateLocalMatrix();
		UpdateWorldMatrix();
	}
	
	void Transform::UpdateLocalMatrix()
	{
		this->mat = 
			glm::translate(glm::mat4(1), position) * 
			glm::toMat4(rot)*
			glm::scale(glm::mat4(1),scale);

		//this->mat = glm::translate(glm::mat4(1.0f), position);

	}

	void Transform::UpdateWorldMatrix()
	{
		if (this->entity  && this->entity->parent)
			this->w_mat = this->entity->parent->GetTransform()->w_mat * this->mat;
		else
			this->w_mat = this->mat;
		//this->mat = glm::translate(glm::mat4(1.0f), position);

	}


}
