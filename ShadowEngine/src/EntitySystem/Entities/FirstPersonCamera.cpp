#include "shpch.h"
#include "FirstPersonCamera.h"

#include "ShadowInput/ShadowAction.h"
#include "ShadowInput/Bindings/Binding1D.h"
#include "ShadowInput/Bindings/KeyboardBinding.h"
#include "ShadowInput/Bindings/MousePositionBinding.h"
#include "ShadowInput/Bindings/MouseButtonBinding.h"
#include "ShadowInput/Bindings/BindingAND.h"

#include "EntitySystem/EntityManager.h"

#include "EntitySystem/Scene.h"

#include <iostream>

#include <SDL.h>

void FirstPersonCamera::Build()
{
	cam = AddInternalChildEntity<Camera>();
	cam->name = "Camera";
}

void FirstPersonCamera::Init()
{
	//cam = scene->AddEntity<Camera>();

	cam->SetCameraType(CameraType::Perspective);
	cam->transform.SetPosition({ 0,0.0f,0.0f });




	forward = new ShadowEngine::InputSystem::ShadowAction<float>(
		"Forward",
		new ShadowEngine::InputSystem::Binding1D(
			new ShadowEngine::InputSystem::KeyboardBinding(SDL_SCANCODE_W),
			new ShadowEngine::InputSystem::KeyboardBinding(SDL_SCANCODE_S)
		),
		true
		);

	side = new ShadowEngine::InputSystem::ShadowAction<float>(
		"Side",
		new ShadowEngine::InputSystem::Binding1D(
			new ShadowEngine::InputSystem::KeyboardBinding(SDL_SCANCODE_D),
			new ShadowEngine::InputSystem::KeyboardBinding(SDL_SCANCODE_A)
		),
		true
		);

	mouse = new ShadowEngine::InputSystem::ShadowAction<glm::vec2>(
		"Mouse",
		new ShadowEngine::InputSystem::MousePositionBinding()
		);

	mouseButton = new ShadowEngine::InputSystem::ShadowAction<bool>(
		"MouseButton",
		new ShadowEngine::InputSystem::MouseButtonBinding(SDL_BUTTON_LEFT),
		true
		);
}

void FirstPersonCamera::Update(float dt)
{
	auto pos = this->GetPosition();
	glm::vec3 rot = this->GetRotation();
	//glm::vec3 rot(0,0,0);

	if (forward->GetPerformed()) {
		pos += this->transform.GetForward() * (forward->GetData() * 0.001f * dt);
	}

	if (side->GetPerformed()) {
		pos += this->transform.GetRight() * ( side->GetData() * -0.001f * dt);
	}

	if (mouseButton->GetState() == ShadowEngine::InputSystem::ActionState::Progress && mouse->GetPerformed()) {

		rot.y += mouse->GetData().x * speed;
		rot.x += mouse->GetData().y * speed;
		//rot.x= glm::clamp(rot.x,-360.0f / 2, +360.0f / 2);
		//rot.y = glm::clamp(rot.y, -360.0f / 2, +360.0f / 2);

		//std::cout << "Nice";
	}

	//rot.y += 1.f;
	
	

	this->SetRotation(rot);
	this->SetPosition(pos);

}
