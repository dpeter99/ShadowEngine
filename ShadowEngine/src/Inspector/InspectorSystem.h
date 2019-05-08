#pragma once

#include <map>
#include "Inspector.h"

class InspectorSystem
{

	static std::map<std::string, Inspector*> inspectors;

public:

	static void AddInspector(std::string name, Inspector* inspector);

	static void Draw(SHObject& obj);

	static void DrawSub(SHObject& obj);
};

