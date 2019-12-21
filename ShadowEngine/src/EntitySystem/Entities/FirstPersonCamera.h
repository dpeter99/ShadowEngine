#pragma once
#include "Camera.h"
#include "EntitySystem/SceneEntity.h"
#include "ShadowInput/ShadowAction.h"

class FirstPersonCamera: public ShadowEngine::EntitySystem::SceneEntity
{
	SHObject_Base(FirstPersonCamera)
	Entity_Base(FirstPersonCamera, ShadowEngine::EntitySystem::SceneEntity)

private:
	
	ShadowEngine::EntitySystem::rtm_ptr<Camera> cam;

	ShadowEngine::InputSystem::ShadowAction<float>* forward;

	ShadowEngine::InputSystem::ShadowAction<float>* side;

	ShadowEngine::InputSystem::ShadowAction<glm::vec2>* mouse;

	ShadowEngine::InputSystem::ShadowAction<bool>* mouseButton;
public:
	void Build() override;
	
	void Init() override;

	void Update(float dt) override;
	
};

class FirstPersonCameraInspector : public ShadowEngine::Debug::EntityInspector {

public:
	void Draw(ShadowEngine::EntitySystem::rtm_ptr<ShadowEngine::EntitySystem::Entity>& obj) override {
		//ShadowEngine::EntitySystem::rtm_ptr<Camera> cam = obj;
		DrawTransformInspector((ShadowEngine::EntitySystem::rtm_ptr<ShadowEngine::EntitySystem::SceneEntity>)obj);
	}
};