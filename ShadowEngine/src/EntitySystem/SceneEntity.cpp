#include "shpch.h"
#include "SceneEntity.h"

namespace ShadowEngine::EntitySystem {


	void SceneEntity::SetParent(rtm_ptr<Entity> e)
	{
		Entity::SetParent(e);
	}

	ShadowEntity::Transform* SceneEntity::GetTransform()
	{
		return &this->transform;
	}

	
	ShadowEntity::Transform SceneEntity::CalcNewComponentToWorld(
		const ShadowEntity::Transform& NewRelativeTransform) const
	{
		if (this->parent)
		{
			return NewRelativeTransform * *parent->GetTransform();
		}
		else
		{
			return NewRelativeTransform;
		}
	}

	void SceneEntity::SetPosition(glm::vec3 location)
	{
		if (transform.GetPosition() != location) {
			this->transform.SetPosition(location);
			this->w_transform = CalcNewComponentToWorld(this->transform);
			TransformUpdated();
		}
	}

	void SceneEntity::SetRotation(glm::vec3 rotation)
	{
		if (transform.GetRotation() != glm::quat(rotation)) {
			this->transform.SetRotation(rotation);
			this->w_transform = CalcNewComponentToWorld(this->transform);
			TransformUpdated();
		}
	}

	void SceneEntity::SetScale(glm::vec3 scale)
	{
		if (transform.GetScale() != scale) {
			this->transform.SetScale(scale);
			this->w_transform = CalcNewComponentToWorld(this->transform);
			TransformUpdated();
		}
	}
	
	void SceneEntity::SetRelativeTransform(const ShadowEntity::Transform& NewTransform)
	{
		this->transform = NewTransform;
		this->w_transform = CalcNewComponentToWorld(NewTransform);
		TransformUpdated();
	}

	glm::vec3 SceneEntity::GetPosition()
	{
		return this->transform.GetPosition();
	}

	glm::vec3 SceneEntity::GetRotation()
	{
		return glm::eulerAngles( this->transform.GetRotation());
	}

	glm::vec3 SceneEntity::GetScale()
	{
		return this->transform.GetScale();
	}

	void SceneEntity::TransformUpdated()
	{

		TransformChanged();

		//This transform has changed so we need to update the children about it
		for each (auto & child in hierarchy)
		{
			child->ParentTransformUpdated();
		}

		for each (auto & child in internalHierarchy)
		{
			child->ParentTransformUpdated();
		}
	}

	void SceneEntity::ParentTransformUpdated()
	{
		//Recalculat the transform, this always uses the parent or world.
		this->w_transform = CalcNewComponentToWorld(this->transform);

		TransformUpdated();
	}
}
