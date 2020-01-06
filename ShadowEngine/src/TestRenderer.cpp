#include "shpch.h"
#include "TestRenderer.h"

#include <glm/gtx/quaternion.hpp>
#include "ShadowRenderer/Renderer.h"
#include <glm\gtx\euler_angles.hpp>

TestRenderer::TestRenderer() {

	ShadowEngine::Rendering::Vertex verts[3] = {
		{glm::vec3(-0.5f, -0.5f, 0.0f),glm::vec3(),glm::vec2(),glm::vec4(1, 0, 0, 1.0)},
		{glm::vec3(0.5f, -0.5f, 0.0f),glm::vec3(),glm::vec2(),glm::vec4(0,1, 0, 1.0f)},
		{glm::vec3(0.0f,  0.5f, 0.0f),glm::vec3(),glm::vec2(),glm::vec4(0, 0, 1, 1.0)}
	};
	uint32_t indices[3] = { 0, 1, 2 };

	m_mesh.reset(new ShadowEngine::Assets::Mesh(verts, sizeof(verts), sizeof(ShadowEngine::Rendering::Vertex), indices, sizeof(indices)));
	
	m_Shader.reset(ShadowEngine::Rendering::Shader::CreateFromCompiled("Shaders/Default-VS.cso", "Shaders/Default-FS.cso"));

	m_Material.reset(new ShadowEngine::Assets::Material(m_Shader));

	m_Material->SetProperty("tint", glm::vec4(1, 0, 0, 1));
	m_Material->UpdateBufferIfDirty(); 
}

void TestRenderer::Update() {
	static int t = 0;
	t++;
	m_Material->SetProperty("tint", glm::vec4(t/1000.0f, 0, 0, 1));
	m_Material->UpdateBufferIfDirty();

	// Triangle
	if(!tri_one)
		tri_one = ShadowEngine::Rendering::Renderer::AddRenderNode(m_mesh,m_Material);

	glm::mat4x4 mat(1.0f);
	mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.5+(t/500.0f),0,0));
	//mat *= glm::eulerAngleYXZ(t / 20.0f, 0.0f, 0.0f);

	tri_one->GetCB()->modelToWorld = mat;
	tri_one->GetCB().Upload();
}