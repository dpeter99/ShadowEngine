#pragma once

#include <map>
#include "Inspector.h"

namespace InspectorSystem {

	class InspectorSystem
	{

		static std::map<std::string, Inspector*> inspectors;

	public:

		static void AddInspector(std::string name, Inspector* inspector);

		static void Draw(ShadowEngine::SHObject& obj);

		static void DrawSub(ShadowEngine::SHObject& obj);
	};

}