#include "shpch.h"
#include "FirstPersonCamera.h"

#include "ShadowInput/ShadowAction.h"
#include "ShadowInput/Bindings/Binding1D.h"
#include "ShadowInput/Bindings/KeyboardBinding.h"

#include "EntitySystem/EntityManager.h"

#include "EntitySystem/ShadowScene.h"

#include <SDL2/SDL.h>

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
}

void FirstPersonCamera::Update()
{
	auto pos = this->transform.GetPosition();

	if (forward->GetPerformed()) {
		pos.z += forward->GetData() * 0.1;
	}

	if (side->GetPerformed()) {
		pos.x += side->GetData() * 0.1;
	}

	this->transform.SetPosition(pos);
	
}
