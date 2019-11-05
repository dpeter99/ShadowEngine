#include "shpch.h"
#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Core/ShadowApplication.h"
#include "ShadowScene/ShadowScene.h"

void Camera::TransformChanged()
{
	switch (type)
	{
	case CameraType::Orthographic:
		ortho_RecalculateViewMatrix();
		break;
	case CameraType::Perspective:
		persp_RecalculateViewMatrix();
		break;
	default:;
	}
}

void Camera::SetCameraType(CameraType t)
{
	type = t;

	switch (type)
	{
	case CameraType::Orthographic:
		ortho_Setup();
		break;
	case CameraType::Perspective:
		persp_Setup();
		break;
	default: ;
	}
	
}

void Camera::ortho_Setup()
{
	//float SceneHeight = 2;
	
	float height = ShadowEngine::ShadowApplication::Get().GetWindow().Height;
	float width = ShadowEngine::ShadowApplication::Get().GetWindow().Width;
	
	float vertical = (ortho_height / 2);
	float horizontal = width / height * (ortho_height / 2);

	//m_ProjectionMatrix = glm::mat4(glm::ortho(-1.6f, 1.6f, -0.9f, 0.9f, -1.0f, 10.0f));
	m_ProjectionMatrix = glm::mat4(glm::ortho(-horizontal, horizontal, -vertical, vertical, -1.0f, 10.0f));

	ortho_RecalculateViewMatrix();
}

void Camera::persp_RecalculateViewMatrix()
{
	m_ViewMatrix = glm::inverse(transform.GetTransformMatrix());
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void Camera::persp_Setup()
{
	float height = ShadowEngine::ShadowApplication::Get().GetWindow().Height;
	float width = ShadowEngine::ShadowApplication::Get().GetWindow().Width;
	
	m_ProjectionMatrix = glm::perspectiveFov(glm::radians(25.0f), width, height, 0.01f, 10.0f);
}

void Camera::ortho_RecalculateViewMatrix()
{
	m_ViewMatrix = glm::inverse(transform.GetTransformMatrix());
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void Camera::Init()
{
	Entity::Init();
	scene->mainCamera = this;
	
}
