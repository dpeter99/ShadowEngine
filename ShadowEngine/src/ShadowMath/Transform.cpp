#include "shpch.h"
#include "Transform.h"

#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace ShadowEngine::ShadowEntity {

	Transform::Transform()
	{
		position = glm::vec3(0, 0, 0);
		scale = glm::vec3(1, 1, 1);
		rot = glm::vec3({0,0,0});
		

		UpdateMatrix();
	}

	Transform::Transform(const Transform& other)
	{
		position = other.position;
		scale = other.scale;
		rot = other.rot;
		

		UpdateMatrix();
	}

	Transform::Transform(const glm::vec3& pos) : position(pos)
	{
		scale = glm::vec3(1, 1, 1);
		rot = glm::vec3({ 0,0,0 });
		
		UpdateMatrix();
	}

	Transform::Transform(const glm::vec3& pos, const glm::vec3& size) :position(pos), scale(size)
	{
		rot = glm::vec3({ 0,0,0 });
		

		UpdateMatrix();
	}

	Transform::Transform(const glm::vec3& pos, const glm::vec3& size, const glm::vec3& rotation)
		:position(pos),
		scale(size),
		rot(rotation)
	{

		UpdateMatrix();
	}

	/*
	Transform::Transform(const glm::vec3& pos, const glm::vec3& size, const glm::vec3& rotation)
		:position(pos),
		scale(size),
		rot(glm::radians(rotation))
	{

		UpdateMatrix();
	}
	*/

	/** Returns Multiplied Transform of 2 FTransforms **/
			///P:\_Other\UnrealEngine\Engine\Source\Runtime\Core\Public\Math\TransformVectorized.h:1480
	Transform Transform::Multiply(const Transform* A, const Transform* B)
	{
		Transform OutTransform;

		//A->DiagnosticCheckNaN_All();
		//B->DiagnosticCheckNaN_All();
		//
		//checkSlow(A->IsRotationNormalized());
		//checkSlow(B->IsRotationNormalized());
		//
		//	When Q = quaternion, S = single scalar scale, and T = translation
		//	QST(A) = Q(A), S(A), T(A), and QST(B) = Q(B), S(B), T(B)
		//
		//	QST (AxB) 
		//
		// QST(A) = Q(A)*S(A)*P*-Q(A) + T(A)
		// QST(AxB) = Q(B)*S(B)*QST(A)*-Q(B) + T(B)
		// QST(AxB) = Q(B)*S(B)*[Q(A)*S(A)*P*-Q(A) + T(A)]*-Q(B) + T(B)
		// QST(AxB) = Q(B)*S(B)*Q(A)*S(A)*P*-Q(A)*-Q(B) + Q(B)*S(B)*T(A)*-Q(B) + T(B)
		// QST(AxB) = [Q(B)*Q(A)]*[S(B)*S(A)]*P*-[Q(B)*Q(A)] + Q(B)*S(B)*T(A)*-Q(B) + T(B)
		//
		//	Q(AxB) = Q(B)*Q(A)
		//	S(AxB) = S(A)*S(B)
		//	T(AxB) = Q(B)*S(B)*T(A)*-Q(B) + T(B)
		//checkSlow(VectorGetComponent(A->Scale3D, 3) == 0.f);
		//checkSlow(VectorGetComponent(B->Scale3D, 3) == 0.f);
		//
		/*
		if (Private_AnyHasNegativeScale(A->Scale3D, B->Scale3D))
		{
			// @note, if you have 0 scale with negative, you're going to lose rotation as it can't convert back to quat
			MultiplyUsingMatrixWithScale(OutTransform, A, B);
		}
		else*/
		{
			// RotationResult = B.Rotation * A.Rotation
			OutTransform.rot = B->rot + A->rot; //VectorQuaternionMultiply2(QuatB, QuatA);

			// TranslateResult = B.Rotate(B.Scale * A.Translation) + B.Translate
			const glm::vec3 ScaledTransA = A->position * B->scale; // VectorMultiply(TranslateA, ScaleB);

			glm::vec3 rotated = glm::rotateX(ScaledTransA, B->rot.x);
			rotated = glm::rotateY(rotated, B->rot.y);
			rotated = glm::rotateZ(rotated, B->rot.z);

			//const glm::vec3 RotatedTranslate = glm::rotate(B->rot, ScaledTransA);
			const glm::vec3 RotatedTranslate = rotated;
			OutTransform.position = RotatedTranslate + B->position;

			// ScaleResult = Scale.B * Scale.A
			OutTransform.scale = A->scale * B->scale;
		}

		return OutTransform;
	}

	void Transform::UpdateMatrix()
	{
		this->mat =
			glm::translate(glm::mat4(1), position) *
			//glm::toMat4(rot) *
			glm::toMat4( glm::quat( glm::radians(rot))) *
			glm::scale(glm::mat4(1), scale);
	}

	glm::mat4 Transform::GetMatrix()
	{
		return mat;
	}

}
