#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "Util/Callback.h"

namespace ShadowEntity {

	class Transform
	{
	public:
		Transform();
		Transform(glm::vec3 pos);
		Transform(glm::vec3 pos, glm::vec3 size);
		Transform(glm::vec3 pos, glm::vec3 size, glm::quat rotation);

		glm::vec3 GetPosition() { return position; }
		void SetPosition(glm::vec3 val) { position = val; UpdateMatrix(); transformChanged(); };

		glm::vec3 GetScale() { return scale; };
		void SetScale(glm::vec3 val) { scale = val; UpdateMatrix(); transformChanged(); };

		glm::quat GetRotation() { return rot; };
		void SetRotation(glm::quat val) { rot = val; UpdateMatrix(); transformChanged(); };

		glm::mat4 GetTransformMatrix() { return mat; };

		Callback transformChanged;

	private:
		void UpdateMatrix();

		glm::vec3 position;
		glm::vec3 scale;
		glm::quat rot;

		glm::mat4 mat;
	};

}