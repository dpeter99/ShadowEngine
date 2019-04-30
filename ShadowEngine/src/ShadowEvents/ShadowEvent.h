#pragma once
#include <ostream>
#include <string>
#include "../Core.h"


#define EVENT_CLASS_TYPE(type)	\
public:				\
	virtual const char* GetName() const override { return  #type; } \
	static const char* GetStaticType() { return #type; }\
	virtual const char* GetType() const override { return GetStaticType(); } \

class ShadowEvent
{
public:
	bool Handled = false;

	virtual const char* GetName() const = 0;
	virtual const char* GetType() const = 0;
	
	virtual std::string ToString() const { return GetName(); }

public:
	ShadowEvent();
	virtual ~ShadowEvent();
};

inline std::ostream& operator<<(std::ostream& os, const class ShadowEvent& e)
{
	return os << e.ToString();
}
