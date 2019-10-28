#include "shpch.h"
#include "TestRenderer.h"

#include <glm/gtx/quaternion.hpp>
#include "ShadowRenderer/Renderer.h"

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

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	// Triangle
	ShadowEngine::Rendering::Renderer::Submit(m_mesh,m_Material);

	// Triangle
	glm::mat4x4 trans;
	glm::translate(trans,{ 0.2,0.2,0 });
	ShadowEngine::Rendering::Renderer::Submit(m_mesh, m_Material,trans);

}