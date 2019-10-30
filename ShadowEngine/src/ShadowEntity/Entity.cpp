//
// Created by dpete on 2/12/2019.
//

#include "shpch.h"

#include <iostream>
#include "Entity.h"
#include "EntityRegistry.h"

namespace ShadowEngine::ShadowEntity
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

	void Entity::SetScene(Scene::ShadowScene* se)
	{
		this->scene = se;
	}

	Entity::Entity()
	{

	}

	Entity::Entity(Scene::ShadowScene* scene)
	{
		this->scene = scene;
	}

	Entity* Entity::Create(Scene::ShadowScene* scene)
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
