#pragma once


#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
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
		struct Transform
		{
			glm::vec3 position;
			glm::vec3 scale;
			glm::quat rot;

			/** Returns Multiplied Transform of 2 FTransforms **/
			Transform* Transform::Multiply(const Transform* A, const Transform* B)
			{
				Transform* OutTransform;
				
				//A->DiagnosticCheckNaN_All();
				//B->DiagnosticCheckNaN_All();

				//checkSlow(A->IsRotationNormalized());
				//checkSlow(B->IsRotationNormalized());

				//	When Q = quaternion, S = single scalar scale, and T = translation
				//	QST(A) = Q(A), S(A), T(A), and QST(B) = Q(B), S(B), T(B)

				//	QST (AxB) 

				// QST(A) = Q(A)*S(A)*P*-Q(A) + T(A)
				// QST(AxB) = Q(B)*S(B)*QST(A)*-Q(B) + T(B)
				// QST(AxB) = Q(B)*S(B)*[Q(A)*S(A)*P*-Q(A) + T(A)]*-Q(B) + T(B)
				// QST(AxB) = Q(B)*S(B)*Q(A)*S(A)*P*-Q(A)*-Q(B) + Q(B)*S(B)*T(A)*-Q(B) + T(B)
				// QST(AxB) = [Q(B)*Q(A)]*[S(B)*S(A)]*P*-[Q(B)*Q(A)] + Q(B)*S(B)*T(A)*-Q(B) + T(B)

				//	Q(AxB) = Q(B)*Q(A)
				//	S(AxB) = S(A)*S(B)
				//	T(AxB) = Q(B)*S(B)*T(A)*-Q(B) + T(B)
				//checkSlow(VectorGetComponent(A->Scale3D, 3) == 0.f);
				//checkSlow(VectorGetComponent(B->Scale3D, 3) == 0.f);

				/*
				if (Private_AnyHasNegativeScale(A->Scale3D, B->Scale3D))
				{
					// @note, if you have 0 scale with negative, you're going to lose rotation as it can't convert back to quat
					MultiplyUsingMatrixWithScale(OutTransform, A, B);
				}
				else*/
				{					
					// RotationResult = B.Rotation * A.Rotation
					OutTransform->rot = B->rot * A->rot; //VectorQuaternionMultiply2(QuatB, QuatA);

					// TranslateResult = B.Rotate(B.Scale * A.Translation) + B.Translate
					const glm::vec3 ScaledTransA = A->position * B->scale; // VectorMultiply(TranslateA, ScaleB);
					const glm::vec3 RotatedTranslate = glm::rotate(B->rot, ScaledTransA);
					OutTransform->position = RotatedTranslate + B->position;

					// ScaleResult = Scale.B * Scale.A
					OutTransform->scale = A->scale * B->scale;
				}

				return OutTransform;
			}
		};
		
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