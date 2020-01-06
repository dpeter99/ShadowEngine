#pragma once

#include <map>
#include "Inspector.h"
#include "EntityInspector.h"
#include "EntitySystem/Entity.h"

namespace ShadowEngine::Debug {

	class InspectorSystem
	{

		static std::map<std::string, Inspector*> inspectors;

		static std::map<std::string, EntityInspector*> entity_inspectors;

	public:

		static void AddInspector(std::string name, Inspector* inspector);

		static void InspectorSystem::AddEntityInspector(std::string name, EntityInspector* inspector);

		static void Draw(ShadowEngine::SHObject& obj);

		static void DrawSub(ShadowEngine::SHObject& obj);

		static void DrawEntityInspector(EntitySystem::rtm_ptr<EntitySystem::Entity> entity);
	};

}