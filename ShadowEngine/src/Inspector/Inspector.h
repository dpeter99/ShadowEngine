#pragma once
#include "Core/SHObject.h"

class Inspector :
	public SHObject
{
	SHObject_Base(Inspector)

public:
	virtual void Draw(SHObject& obj) = 0;
};

