#pragma once

#include "ShadowEntity/SceneEntity.h"

class Light : public ShadowEntity::SceneEntity
{
	SHObject_Base(Light)
	Entity_Base(Light, ShadowEntity::SceneEntity)

public:
	void Render() override;
};