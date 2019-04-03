#pragma once
#include <ostream>
#include <string>
#include "../Core.h"

enum EventCategory
{
	None = 0,
	EventCategoryApplication = BIT(0),
	EventCategoryInput = BIT(1)
};

class ShadowEvent
{
public:
	bool Handled = false;

	virtual const char* GetName() const = 0;
	virtual int GetCategoryFlags() const = 0;
	virtual std::string ToString() const { return GetName(); }

	inline bool IsInCategory(EventCategory category)
	{
		return GetCategoryFlags()& category;
	}



public:
	ShadowEvent();
	virtual ~ShadowEvent();
};

inline std::ostream& operator<<(std::ostream& os, const class ShadowEvent& e)
{
	return os << e.ToString();
}
