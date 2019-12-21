#include "shpch.h"
#include "TestScene.h"
#include <EntitySystem\Entities\Camera.h>
#include "EntitySystem/Entities/MeshRenderer.h"
#include "EntitySystem/Entities/FirstPersonCamera.h"
#include "ShadowAsset/Assets/Textures/Texture.h"
#include "ShadowAsset/Assets/Textures/TextureCubeMap.h"
#include "EntitySystem/Entities/SkySphere.h"

void TestScene::Init()
{
	//auto c = AddEntity<Camera>();
	//c->SetCameraType(CameraType::Perspective);
	//c->transform.SetPosition({ 0,0.0f,-10.0f });

	auto sky = AddEntity<SkySphere>();
	sky->name = "Sky";
	

	auto fps = AddEntity< FirstPersonCamera>();
	fps->name = "Fps Camera";
	
	auto env_map = std::make_shared<ShadowEngine::Assets::TextureCubeMap>("./Resources/Textures/giraffe.png");
	env_map->Upload();
	
	auto m_model = ShadowEngine::Assets::Mesh::LoadModel_obj("giraffe.obj");

	auto m_Shader = ShadowEngine::Ref<ShadowEngine::Rendering::Shader>(ShadowEngine::Rendering::Shader::CreateFromCompiled("Shaders/Default-VS.cso", "Shaders/Default-FS.cso"));

	auto m_Material = std::make_shared<ShadowEngine::Assets::Material>(m_Shader);

	m_Material->SetProperty("tint", glm::vec4(1, 1, 1, 1));

	auto Texture = std::make_shared<ShadowEngine::Assets::Texture2D>("./Resources/Textures/giraffe.png");
	Texture->Upload();
	m_Material->SetTexture("Mat_Tex", Texture);
	m_Material->SetTexture("Mat_Env", env_map);
	
	m_Material->UpdateBufferIfDirty();
	//m_Material->SetProperty("o_color", glm::vec4(1,1, 1, 1));
	
	auto r = AddEntity<MeshRenderer>();
	r->name = "Giraffe";
	r->transform.SetPosition(glm::vec3(0, 0, 0));
	r->transform.SetScale({ 1.0f,1.0f,1.0f });
	
	r->SetMesh(m_model);
	r->SetMaterial(m_Material);
	
	//Scene::Init();
}
