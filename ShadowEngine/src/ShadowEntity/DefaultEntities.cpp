//
// Created by dpete on 2/22/2019.
//

#include "shpch.h"

#include "EntityRegistry.h"
#include "Entity.h"

#include "Entities/Player.h"
#include "Entities/Light.h"

namespace ShadowEngine::ShadowEntity
{
	void EntityRegistry::PreRegisterDefaults()
	{
		this->RegisterEntity("info_player_start", new Player());
		this->RegisterEntity("light", new Light());
	}
}
