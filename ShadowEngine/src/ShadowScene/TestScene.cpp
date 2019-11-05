#include "shpch.h"
#include "TestScene.h"
#include <ShadowEntity\Entities\Camera.h>
#include "ShadowEntity/Entities/MeshRenderer.h"

void TestScene::Init()
{
	Camera* c = AddNewInstance<Camera>();
	c->SetCameraType(CameraType::Perspective);
	c->transform.SetPosition({ 0,0.0f,-10.0f });

	auto m_model = ShadowEngine::Assets::Mesh::LoadModel_obj("3Burst_Hand_Gun_0001x.obj");

	auto m_Shader = ShadowEngine::Ref<ShadowEngine::Rendering::Shader>(ShadowEngine::Rendering::Shader::CreateFromCompiled("Shaders/Default-VS.cso", "Shaders/Default-FS.cso"));

	auto m_Material = std::make_shared<ShadowEngine::Assets::Material>(m_Shader);
	
	MeshRenderer* r = AddNewInstance<MeshRenderer>();
	r->transform.SetPosition(glm::vec3(0, 0, 5));
	r->transform.SetScale({ 0.001f,0.001f,0.001f });
	
	r->SetMesh(m_model);
	r->SetMaterial(m_Material);
	
	ShadowScene::Init();
}
