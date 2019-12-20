#include "shpch.h"

#include <iostream>
#include "Entity.h"
#include "EntityRegistry.h"

namespace ShadowEngine::EntitySystem
{
	
	EntityFlags Entity::GetFlags()
	{
		return EntityFlags::NONE;
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

	void Entity::Build()
	{
	}

	void Entity::Init()
	{
	}

	std::ostream& operator<<(std::ostream& os, const Entity& dt)
	{
		os << dt.GetType();
		return os;
	}
}
