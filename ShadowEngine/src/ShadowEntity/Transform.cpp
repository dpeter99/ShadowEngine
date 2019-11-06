#include "shpch.h"
#include "Transform.h"

#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

	void Transform::UpdateMatrix()
	{
		this->mat = 
			glm::translate(glm::mat4(1), position) * 
			glm::toMat4(rot)*
			glm::scale(glm::mat4(1),scale);

		//this->mat = glm::translate(glm::mat4(1.0f), position);

	}


}