#pragma once
#include "Core/IGame.h"

class ShadowLight : public ShadowEngine::IGame
{
public:
	void Init() override;
	void Start() override;
	void Stop() override;
};
