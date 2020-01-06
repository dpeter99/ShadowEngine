#pragma once

#include <list>
#include <map>


#include "Entity.h"

//#include "Entities/Player.h"


namespace ShadowEngine::EntitySystem
{
	class EntityRegistry
	{
	private:


	public:
		static EntityRegistry* _registry;

		EntityRegistry();


		//Pre registry
		std::map<std::string, Entity*> EntityRegistryMap;


		bool RegisterEntity(std::string, Entity* entityTemplate);

		void ListPreRegisteredEntitys();


		//Create a instance of the specified Entity
		Entity* InstaciateEntity(std::string);


		//Will be generated at compile time
		//For now manually made
		void PreRegisterDefaults();
	};
}

