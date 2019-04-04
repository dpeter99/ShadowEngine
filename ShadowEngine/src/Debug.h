#pragma once
#include "ShadowModules/ShadowModule.h"
#include "ShadowEvents/IShadowEventListener.h"

class Debug :
	public ShadowModule , public IShadowEventListener
{
public:

	virtual void Init() override;

	virtual void OnEvent(ShadowEvent& e) override;

	Debug();
	virtual ~Debug();
};

