#pragma once

#include "EntitySystem/SceneEntity.h"

class Light : public ShadowEngine::EntitySystem::SceneEntity
{
	SHObject_Base(Light)
	Entity_Base(Light, SceneEntity)

public:
	void Render() override;
};