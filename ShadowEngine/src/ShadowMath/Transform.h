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
		//Transform(const glm::vec3& pos, const glm::vec3& size, const glm::quat& rotation);
		Transform(const glm::vec3& pos, const glm::vec3& size, const glm::vec3& rotation);


		glm::vec3 GetPosition() { return position; }
		void SetPosition(glm::vec3 val) { position = val; UpdateMatrix(); }
		

		glm::vec3 GetScale() { return scale; };
		void SetScale(glm::vec3 val) { scale = val; UpdateMatrix(); };

		//glm::quat GetRotation() { return rot; };
		//void SetRotation(glm::quat val) { rot = val; UpdateMatrix(); };

		//TODO:Fix qats
		glm::vec3 normalizeAngles(glm::vec3 val) {
			val.x = val.x < 0 ? 360 - val.x : val.x;
			val.y = val.y < 0 ? 360 - val.y : val.y;
			val.z = val.z < 0 ? 360 - val.z : val.z;

			return val;
		}

		/*
		glm::vec3 GetEulerRotation() { return glm::degrees(glm::eulerAngles(rot)); };
		void SetEulerRotation(glm::vec3 val) { 
			rot = glm::quat(glm::radians(normalizeAngles(val)));			

			

			UpdateMatrix(); 
		};

		void RotateByEulerRotation(glm::vec3 val) {
			rot *= glm::quat(glm::radians(val));

			UpdateMatrix();
		};
		*/

		glm::vec3 GetEulerRotation() { return rot; };
		void SetEulerRotation(glm::vec3 val) { rot = val; UpdateMatrix(); };

		glm::vec3 GetForward() { 
			glm::vec3 front;
			front.x = cos(glm::radians(rot.x)) * cos(glm::radians(rot.y));
			front.y = sin(glm::radians(rot.x));
			front.z = cos(glm::radians(rot.x)) * sin(glm::radians(rot.y));
			return glm::normalize(front);
			//return glm::rotate(glm:: glm::vec3(0, 0, 1) * rot; 
		};

		glm::vec3 GetRight() {
			return glm::normalize(glm::cross(GetForward(), {0,1,0}));
		}

		glm::vec3 GetUp() {
			return glm::normalize(glm::cross(GetRight(), GetForward()));
		}

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
		glm::vec3 rot;

		//glm::quat rot;

		glm::mat4 mat;
	};

}
