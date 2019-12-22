#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace ShadowEngine::ShadowEntity {

	class Transform
	{
	public:
		Transform();
		Transform(const Transform& other);
		Transform(const glm::vec3& pos);
		Transform(const glm::vec3& pos, const glm::vec3& size);
		Transform(const glm::vec3& pos, const glm::vec3& size, const glm::quat& rotation);
		Transform(const glm::vec3& pos, const glm::vec3& size, const glm::vec3& rotation);


		glm::vec3 GetPosition() { return position; }
		void SetPosition(glm::vec3 val) { position = val; UpdateMatrix(); }
		

		glm::vec3 GetScale() { return scale; };
		void SetScale(glm::vec3 val) { scale = val; UpdateMatrix(); };

		//glm::quat GetRotation() { return rot; };
		//void SetRotation(glm::quat val) { rot = val; UpdateMatrix(); };

		//TODO:Fix qats
		glm::vec3 GetEulerRotation() { return glm::degrees(glm::eulerAngles(rot)); };
		void SetEulerRotation(glm::vec3 val) { rot = glm::quat(glm::radians(val)); UpdateMatrix(); };

		//glm::vec3 GetEulerRotation() { return rot_vec; };
		//void SetEulerRotation(glm::vec3 val) { rot_vec = val; UpdateMatrix(); };

		glm::vec3 GetForward() { return glm::vec3(0, 0, 1) * rot; };
		glm::vec3 GetLeft() { return glm::vec3(1, 0, 0) * rot; };

		static Transform Multiply(const Transform* A, const Transform* B);
		Transform operator*(const Transform& Other) const
		{
			Transform Output = Multiply(this, &Other);
			return Output;
		}
		
		glm::mat4 GetTransformMatrix() { return mat; };

		void UpdateMatrix();

		glm::mat4 GetMatrix();;
	private:


		glm::vec3 position;
		glm::vec3 scale;
		glm::quat rot;

		glm::mat4 mat;
	};

}
