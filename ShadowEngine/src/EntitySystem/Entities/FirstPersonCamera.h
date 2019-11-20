#pragma once
#include "Camera.h"
#include "EntitySystem/SceneEntity.h"

class FirstPersonCamera: public ShadowEngine::EntitySystem::SceneEntity
{
	SHObject_Base(FirstPersonCamera)
	Entity_Base(FirstPersonCamera, ShadowEngine::EntitySystem::SceneEntity)

private:
	ShadowEngine::Ref<Camera> cam;

public:
	void Init() override;
};

