#pragma once
#include "Core/IGame.h"

class TestGame : public ShadowEngine::IGame
{
public:
	void Init() override;
	void Start() override;
	void Stop() override;
};

