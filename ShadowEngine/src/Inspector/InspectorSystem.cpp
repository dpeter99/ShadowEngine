#include "shpch.h"
#include "InspectorSystem.h"

#include <imgui.h>

namespace ShadowEngine::Debug {

	std::map<std::string, Inspector*> InspectorSystem::inspectors;

	std::map<std::string, EntityInspector*> InspectorSystem::entity_inspectors;

	void InspectorSystem::AddInspector(std::string name, Inspector* inspector)
	{
		inspectors[name] = inspector;
	}

	void InspectorSystem::AddEntityInspector(std::string name, EntityInspector* inspector)
	{
		entity_inspectors[name] = inspector;
	}

	void InspectorSystem::Draw(SHObject& obj)
	{
		if (inspectors.find(obj.GetType()) != inspectors.end())
		{
			inspectors[obj.GetType()]->Draw(obj);
		}

	}

	void InspectorSystem::DrawSub(SHObject& obj)
	{
		::ImGui::Indent();
		Draw(obj);
		::ImGui::Unindent();
	}

	void InspectorSystem::DrawEntityInspector(EntitySystem::rtm_ptr<EntitySystem::Entity> entity)
	{
		if (entity_inspectors.find(entity->GetType()) != entity_inspectors.end())
		{
			entity_inspectors[entity->GetType()]->Draw(entity);
		}
	}
}