//
// Created by dpete on 2/15/2019.
//

#include "shpch.h"

#include <iostream>
#include "EntityRegistry.h"

namespace ShadowEntity
{
	//PreRegistry

	bool EntityRegistry::RegisterEntity(std::string id, Entity* entityTemplate)
	{
		EntityRegistryMap[id] = entityTemplate;
		return true;
	}

	void EntityRegistry::ListPreRegisteredEntitys()
	{
		for (auto it = EntityRegistryMap.begin(); it != EntityRegistryMap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
	}

	//Registry
	EntityRegistry* EntityRegistry::_registry = nullptr;

	EntityRegistry::EntityRegistry()
	{
		//Setup

		if (_registry != nullptr)
		{
			throw "Registry already present, there can only be one!";
		}
		std::cout << "EntityRegistrySetup \n";
		PreRegisterDefaults();
		_registry = this;
	}

	Entity* EntityRegistry::InstaciateEntity(std::string id)
	{
		//return this->EntityRegistryMap[id]->Create();
		return nullptr;
	}
}
