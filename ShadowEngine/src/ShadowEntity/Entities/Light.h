#pragma once

#include "ShadowEntity/SceneEntity.h"

class Light : public ShadowEngine::ShadowEntity::SceneEntity
{
	SHObject_Base(Light)
	Entity_Base(Light, SceneEntity)

public:
	void Render() override;
};