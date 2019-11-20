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

	void Entity::Update()
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

	void Entity::SetScene(Scene* se)
	{
		this->scene = se;
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
