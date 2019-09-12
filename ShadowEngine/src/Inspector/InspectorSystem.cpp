#include "shpch.h"
#include "InspectorSystem.h"
#include "imgui.h"


std::map<std::string, InspectorSystem::Inspector*> InspectorSystem::InspectorSystem::inspectors;

void InspectorSystem::InspectorSystem::AddInspector(std::string name, Inspector* inspector)
{
	inspectors[name] = inspector;
}

void InspectorSystem::InspectorSystem::Draw(ShadowEngine::SHObject& obj)
{
	if(inspectors.find(obj.GetType()) != inspectors.end())
	{
		inspectors[obj.GetType()]->Draw(obj);
	}

}

void InspectorSystem::InspectorSystem::DrawSub(ShadowEngine::SHObject& obj)
{
	ImGui::Indent();
	Draw(obj);
	ImGui::Unindent();
}
