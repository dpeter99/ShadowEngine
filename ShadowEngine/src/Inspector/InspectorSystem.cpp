#include "shpch.h"
#include "InspectorSystem.h"
#include "imgui.h"


std::map<std::string, Inspector*> InspectorSystem::inspectors;

void InspectorSystem::AddInspector(std::string name, Inspector* inspector)
{
	inspectors[name] = inspector;
}

void InspectorSystem::Draw(SHObject& obj)
{
	if(inspectors.find(obj.GetType()) != inspectors.end())
	{
		inspectors[obj.GetType()]->Draw(obj);
	}

}

void InspectorSystem::DrawSub(SHObject& obj)
{
	ImGui::Indent();
	Draw(obj);
	ImGui::Unindent();
}
