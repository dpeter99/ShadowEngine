#pragma once

#include <map>
#include <list>
#include <string>

namespace ShadowEngine::SFF {

	class SFFElement
	{
	public:
		SFFElement* parent;

		std::string name;

		bool isBlock;

		std::string value;
		typedef std::map<std::string, SFFElement*> ChildrenMap;

		//std::list<SFFElement*> properties_old;
		std::map<std::string, SFFElement*> children;

		std::string GetStringProperty(std::string name);

		//TODO make this return a ref not a pointer
		SFFElement* GetFirstChild();

		//TODO make this return a ref not a pointer
		SFFElement* GetChildByIndex(int i);
		//TODO make this return a ref not a pointer
		SFFElement* GetChildByName(std::string name);

		~SFFElement();

	};
}