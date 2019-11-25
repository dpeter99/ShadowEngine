//
// Created by dpete on 2/12/2019.
//

#include "shpch.h"

#include <iostream>
#include "Entity.h"
#include "EntityRegistry.h"

namespace ShadowEngine::EntitySystem
{
	void Entity::Start()
	{
	}

	void Entity::Update(float dt)
	{
	}

	void Entity::LateUpdate()
	{
	}

	void Entity::Render()
	{
	}

	void Entity::LateRender()
	{
	}

	EntityFlags Entity::GetFlags()
	{
		return EntityFlags::NONE;
	}

	void Entity::TransformChanged(bool self)
	{
		for each (auto e in internalHierarchy)
		{
			e->TransformChanged(false);
		}
	}

	ShadowEntity::Transform* Entity::GetTransform()
	{
		return parent->GetTransform();
	}

	void Entity::SetScene(Scene* se)
	{
		this->scene = se;
	}

	void Entity::SetParent(rtm_ptr<Entity> e)
	{
		this->parent = e;
	}

	Entity::Entity()
	{

	}

	Entity::Entity(Scene* scene)
	{
		this->scene = scene;
	}

	Entity* Entity::Create(Scene* scene)
	{
		throw "The base entity cannot be instantiated";
	}

	void Entity::Init()
	{
	}

	std::ostream& operator<<(std::ostream& os, const Entity& dt)
	{
		os << dt.GetType();
		return os;
	}

	//bool Entity::registered = ShadowEntity::EntityRegistry::PreRegisterEntity(id);
}
