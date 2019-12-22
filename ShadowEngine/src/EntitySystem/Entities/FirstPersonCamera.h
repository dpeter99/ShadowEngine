#pragma once
#include "Camera.h"
#include "EntitySystem/SceneEntity.h"
#include "ShadowInput/ShadowAction.h"

#include "imgui.h"

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
	float speed = 1;

	void Build() override;
	
	void Init() override;

	void Update(float dt) override;

	friend class FirstPersonCameraInspector;
	
};

class FirstPersonCameraInspector : public ShadowEngine::Debug::EntityInspector {

public:
	void Draw(ShadowEngine::EntitySystem::rtm_ptr<ShadowEngine::EntitySystem::Entity>& obj) override {
		
		DrawTransformInspector((ShadowEngine::EntitySystem::rtm_ptr<ShadowEngine::EntitySystem::SceneEntity>)obj);

		ShadowEngine::EntitySystem::rtm_ptr<FirstPersonCamera> cam = obj;
		ImGui::SliderFloat("Speed", &cam->speed, 0, 2);
	}
};