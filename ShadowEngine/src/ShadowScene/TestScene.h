#pragma once
#include "ShadowScene/ShadowScene.h"

class TestScene : public ShadowEngine::Scene::ShadowScene
{
	virtual ~TestScene() = default;

	void Init() override;
};

