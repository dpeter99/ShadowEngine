#pragma once
#include "Core/Core.h"
#include "ShadowRenderer/Shader.h"
#include "ShadowRenderer/VertexArray.h"
#include "ShadowRenderer/Texture.h"
#include "ShadowRenderer/OrthographicCamera.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ShadowEntity/Entities/Camera.h"
#include <ShadowRenderer\Shader.h>

class TestRenderer
{
	ShadowEngine::Ref<ShadowEngine::Rendering::Shader> m_Shader;
	ShadowEngine::Ref<ShadowEngine::Rendering::VertexArray> m_VertexArray;

	ShadowEngine::Ref<ShadowEngine::Rendering::Shader> m_FlatColorShader, m_TextureShader;
	ShadowEngine::Ref<ShadowEngine::Rendering::VertexArray> m_SquareVA;

	ShadowEngine::Ref<ShadowEngine::Rendering::Texture2D> m_Texture, m_ChernoLogoTexture;

	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };

public:
	TestRenderer();
	void Update();
};

