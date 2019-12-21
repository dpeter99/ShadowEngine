#include "shpch.h"

#include "Debug/Debug.h"

#include "InspectorSystem.h"

#include "EntitySystem/Entities/Camera.h"
#include "EntitySystem/Entities/FirstPersonCamera.h"
#include "EntitySystem/Entities/Light.h"
#include "EntitySystem/Entities/MeshRenderer.h"


void RegisterEntityInspectors() {
	ShadowEngine::Debug::InspectorSystem::AddEntityInspector(Camera::Type(), new CameraInspector());
	ShadowEngine::Debug::InspectorSystem::AddEntityInspector(FirstPersonCamera::Type(), new FirstPersonCameraInspector());
	ShadowEngine::Debug::InspectorSystem::AddEntityInspector(Light::Type(), new LightInspector());
	ShadowEngine::Debug::InspectorSystem::AddEntityInspector(MeshRenderer::Type(), new MeshRendererInspector());
}