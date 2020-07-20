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

	std::list<SFFElement*> properties_old;
	std::map<std::string, SFFElement*> properties;

	std::string GetStringProperty(std::string name);

	~SFFElement();
	
};
