#include "shpch.h"
#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Core/ShadowApplication.h"

void Camera::TransformChanged()
{
	RecalculateViewMatrix();
}

Camera::Camera(CameraType t) : type(t)
{
	if (t == CameraType::Orthographic)
		SetupOrthographic();
}

void Camera::SetupOrthographic()
{
	float SceneHeight = 2;
	
	int height = ShadowApplication::Get().GetWindow().Height;
	int width = ShadowApplication::Get().GetWindow().Width;
	
	float vertical = (SceneHeight / 2);
	float horizontal = width / height * (SceneHeight / 2);

	//m_ProjectionMatrix = glm::mat4(glm::ortho(-1.6f, 1.6f, -0.9f, 0.9f, -1.0f, 10.0f));
	m_ProjectionMatrix = glm::mat4(glm::ortho(-horizontal, horizontal, -vertical, vertical, -1.0f, 10.0f));
	m_ViewMatrix = glm::mat4(1.0f);
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;

	RecalculateViewMatrix();
}

void Camera::RecalculateViewMatrix()
{
	m_ViewMatrix = glm::inverse(transform.GetTransformMatrix());
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}
