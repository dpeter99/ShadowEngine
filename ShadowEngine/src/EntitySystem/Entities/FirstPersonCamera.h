#pragma once
#include "Camera.h"
#include "EntitySystem/SceneEntity.h"
#include "ShadowInput/ShadowAction.h"

class FirstPersonCamera: public ShadowEngine::EntitySystem::SceneEntity
{
	SHObject_Base(FirstPersonCamera)
	Entity_Base(FirstPersonCamera, ShadowEngine::EntitySystem::SceneEntity)

private:
	std::string a = "FPS Cam ABCD";
	
	ShadowEngine::EntitySystem::rtm_ptr<Camera> cam;

	ShadowEngine::InputSystem::ShadowAction<float>* forward;

	ShadowEngine::InputSystem::ShadowAction<float>* side;

	ShadowEngine::InputSystem::ShadowAction<glm::vec2>* mouse;

	ShadowEngine::InputSystem::ShadowAction<bool>* mouseButton;
public:
	void Init() override;

	void Update(float dt) override;
};

