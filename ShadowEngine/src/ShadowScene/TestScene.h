#pragma once
#include "EntitySystem/ShadowScene.h"

class TestScene : public ShadowEngine::EntitySystem::Scene
{
	virtual ~TestScene() = default;

	void Init() override;
};

