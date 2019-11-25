#include "shpch.h"
#include "FirstPersonCamera.h"

#include "ShadowInput/ShadowAction.h"
#include "ShadowInput/Bindings/Binding1D.h"
#include "ShadowInput/Bindings/KeyboardBinding.h"
#include "ShadowInput/Bindings/MousePositionBinding.h"
#include "ShadowInput/Bindings/MouseButtonBinding.h"
#include "ShadowInput/Bindings/BindingAND.h"

#include "EntitySystem/EntityManager.h"

#include "EntitySystem/ShadowScene.h"

#include <SDL.h>

void FirstPersonCamera::Init()
{
	cam = scene->AddEntity<Camera>();
	this->internalHierarchy.push_back(cam);
	cam->SetParent(this);

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
	auto pos = this->transform.GetPosition();
	auto rot = this->transform.GetEulerRotation();

	if (forward->GetPerformed()) {
		pos += this->transform.GetForward() * (forward->GetData() * 0.001f * dt);
	}

	if (side->GetPerformed()) {
		pos += this->transform.GetLeft() * ( side->GetData() * 0.001f * dt);
	}

	if (mouseButton->GetState() == ShadowEngine::InputSystem::ActionState::Progress && mouse->GetPerformed()) {

		rot.y += mouse->GetData().x * 0.02;
		rot.x += mouse->GetData().y * 0.02;
		rot.x= glm::clamp(rot.x,-360.0f / 2, +360.0f / 2);

		//std::cout << "Nice";
	}

	//rot.y += 0.01f;
	

	this->transform.SetRotation(glm::quat(rot));
	this->transform.SetPosition(pos);

}
