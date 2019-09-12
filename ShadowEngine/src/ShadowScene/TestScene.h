#pragma once
#include "ShadowScene/ShadowScene.h"

class TestScene : public ShadowScene
{
	virtual ~TestScene() = default;

	void Init() override;
};

