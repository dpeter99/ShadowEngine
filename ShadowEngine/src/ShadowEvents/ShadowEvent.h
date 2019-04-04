#pragma once
#include <ostream>
#include <string>
#include "../Core.h"


#define EVENT_CLASS_TYPE(type) virtual const char* GetName() const override { return #type; }

class ShadowEvent
{
public:
	bool Handled = false;

	virtual const char* GetName() const = 0;
	//virtual int GetCategoryFlags() const = 0;
	virtual std::string ToString() const { return GetName(); }

public:
	ShadowEvent();
	virtual ~ShadowEvent();
};

inline std::ostream& operator<<(std::ostream& os, const class ShadowEvent& e)
{
	return os << e.ToString();
}
