#pragma once
#include "ShadowEntity/SceneEntity.h"
#include "glm/glm.hpp"



class Camera :
	public ShadowEntity::SceneEntity
{
public:
	const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
	const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
	const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

	
	

	enum CameraType { Orthographic };

	Camera(CameraType t);
	void SetupOrthographic();

	CameraType type;

private:
	void TransformChanged() override;
	void RecalculateViewMatrix();
	
	glm::mat4 m_ProjectionMatrix;
	glm::mat4 m_ViewMatrix;
	glm::mat4 m_ViewProjectionMatrix;

public:
	void Init() override;
	
};

