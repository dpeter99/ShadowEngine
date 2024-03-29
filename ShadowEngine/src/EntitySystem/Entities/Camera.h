#pragma once
#include "glm/glm.hpp"
#include "EntitySystem/SceneEntity.h"
#include "Inspector/EntityInspector.h"
#include "Internal/Inspectors/DefaultInspectors.h"

enum class CameraType {
	Orthographic,
	Perspective
};

class Camera :
	public ShadowEngine::EntitySystem::SceneEntity
{
	
	SHObject_Base(Camera)
	Entity_Base(Camera, ShadowEngine::EntitySystem::SceneEntity);

private:
	void TransformChanged() override;
	
	void ortho_RecalculateViewMatrix();
	void ortho_Setup();

	void persp_RecalculateViewMatrix();
	void persp_Setup();

	glm::mat4 m_ProjectionMatrix;
	glm::mat4 m_ViewMatrix;
	glm::mat4 m_ViewProjectionMatrix;

	CameraType type;


	float ortho_height = 2;
	
public:
	const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
	const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
	const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

	void SetCameraType(CameraType t);;

public:
	void Init() override;
	

};

class CameraInspector : public ShadowEngine::Debug::EntityInspector {

public:
	void Draw(ShadowEngine::EntitySystem::rtm_ptr<ShadowEngine::EntitySystem::Entity>& obj) override {
		//ShadowEngine::EntitySystem::rtm_ptr<Camera> cam = obj;
		DrawTransformInspector((ShadowEngine::EntitySystem::rtm_ptr<ShadowEngine::EntitySystem::SceneEntity>)obj);
	}
};