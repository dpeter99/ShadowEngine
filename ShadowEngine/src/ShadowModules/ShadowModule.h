#pragma once
#include "ShadowEvents/ShadowEvent.h"

class ShadowModule
{
public:

	virtual void Init() = 0;

	ShadowModule();
	virtual ~ShadowModule();
};
