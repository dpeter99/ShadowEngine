#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Entity.h"
#include "ShadowMath/Transform.h"
#include "EntitySystem\EntityBase.h"
#include "EntitySystem\ShadowScene.h"

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
		ShadowEntity::Transform transform;
		ShadowEntity::Transform w_transform;

	public:
		SceneEntity() :Entity() 
		{
			scene = nullptr;
			this->transform = ShadowEntity::Transform({ 0,0,0 });
			this->w_transform = CalcNewComponentToWorld(this->transform);
		}

		SceneEntity(Scene* scene) : Entity(scene)
		{
			this->transform = ShadowEntity::Transform({ 0,0,0 });
			this->w_transform = CalcNewComponentToWorld(this->transform);
		};



		void SetParent(rtm_ptr<Entity> e) override;

		virtual ShadowEntity::Transform* GetTransform();

		ShadowEntity::Transform CalcNewComponentToWorld(const ShadowEntity::Transform& NewRelativeTransform) const;

		/**
		 * Sets the position of the entity relative to it's parent or the world.
		 *
		 * \brief
		 *
		 * \param Position The new position of this entity
		 */
		void SetPosition(glm::vec3 Position);
		/**
		 * Sets the Rotation of the entity relative to it's parent or the world.
		 *
		 * \brief
		 *
		 * \param Rotation The new Rotation of this entity
		 */
		void SetRotation(glm::vec3 Rotation);
		/**
		 * Sets the Size of the entity relative to it's parent or the world.
		 *
		 * \brief
		 *
		 * \param Size The new Size of this entity
		 */
		void SetScale(glm::vec3 Size);
		/**
		 * Sets the transform of the entity relative to it's parent or the world.
		 *
		 * \brief
		 *
		 * \param Transform The new Transform of this entity
		 */
		void SetRelativeTransform(const ShadowEntity::Transform& Transform);

		/**
		 * Sets the position of the entity relative to it's parent or the world.
		 *
		 * \brief
		 *
		 * \param Position The new position of this entity
		 */
		glm::vec3 GetPosition();
		/**
		 * Sets the Rotation of the entity relative to it's parent or the world.
		 *
		 * \brief
		 *
		 * \param Rotation The new Rotation of this entity
		 */
		glm::vec3 GetRotation();
		/**
		 * Sets the Size of the entity relative to it's parent or the world.
		 *
		 * \brief
		 *
		 * \param Size The new Size of this entity
		 */
		glm::vec3 GetScale();

		void RotateBy(glm::vec3 rotation);

		glm::mat4 GetWorldTransformMatrix();

		///Called after the transform of this was updated manually
		void TransformUpdated();
	protected:
		void ParentTransformUpdated() override;
	};

}