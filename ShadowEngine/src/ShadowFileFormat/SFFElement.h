#pragma once

#include <map>
#include <list>
#include <string>

class SFFElement
{
public:
	SFFElement* parent;

	std::string name;

	bool isBlock;

	std::string value;
	typedef std::map<std::string, SFFElement*> ChildrenMap;

	std::list<SFFElement*> properties_old;
	std::map<std::string, SFFElement*> children;

	std::string GetStringProperty(std::string name);

	SFFElement* GetFirstChild();

	SFFElement* GetChildByIndex(int i);
	SFFElement* GetChildByName(std::string name);

	~SFFElement();
	
};
