#pragma once
#include "ShadowEntity/SceneEntity.h"
#include "Camera.h"

class FirstPersonCamera: public ShadowEngine::ShadowEntity::SceneEntity
{
	SHObject_Base(FirstPersonCamera)
	Entity_Base(FirstPersonCamera, ShadowEngine::ShadowEntity::SceneEntity)

private:
	ShadowEngine::Ref<Camera> cam;

public:
	void Init() override;
};

