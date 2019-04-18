#pragma once
#include "ShadowEvents/ShadowEvent.h"

class ShadowModule
{
public:

	virtual void Init() = 0;

	virtual void Update() = 0;

	virtual std::string GetName() = 0;

	ShadowModule();
	virtual ~ShadowModule();
};
