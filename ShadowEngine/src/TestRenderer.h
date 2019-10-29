#pragma once
#include "Core/Core.h"
#include "ShadowRenderer/Shader.h"
//#include "ShadowRenderer/VertexArray.h"
#include "ShadowRenderer/Texture.h"
#include "ShadowRenderer/OrthographicCamera.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ShadowEntity/Entities/Camera.h"
#include <ShadowRenderer\Shader.h>
#include "ShadowAsset/Assets/Mesh.h"
#include "ShadowAsset/Assets/Material.h"

class TestRenderer
{
	
	ShadowEngine::Ref<ShadowEngine::Assets::Mesh> m_mesh;

	ShadowEngine::Ref<ShadowEngine::Rendering::Shader> m_Shader;

	ShadowEngine::Ref<ShadowEngine::Assets::Material> m_Material;
	
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };

public:
	TestRenderer();
	void Update();
};

