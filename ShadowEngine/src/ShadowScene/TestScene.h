#pragma once
#include "EntitySystem/Scene.h"

class TestScene : public ShadowEngine::EntitySystem::Scene
{
	virtual ~TestScene() = default;

	void Init() override;
};

