//
// Created by dpete on 2/12/2019.
//

#include <iostream>
#include "Entity.h"
#include "EntityRegistry.h"

namespace ShadowEntity
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

	void Entity::Draw()
	{
	}

	Entity* Entity::Create()
	{
		throw "The base entity cannot be instantiated";
	}

	Entity::~Entity()
	{
	}

	Entity::Entity()
	{
	}

	std::string Entity::id = "Base";

	std::ostream& operator<<(std::ostream& os, const Entity& dt)
	{
		os << dt.id;
		return os;
	}

	//bool Entity::registered = ShadowEntity::EntityRegistry::PreRegisterEntity(id);
}
