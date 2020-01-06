#include "shpch.h"
#include "SkySphere.h"
#include "EntitySystem/ShadowScene.h"
#include "ShadowAsset/Assets/Textures/TextureCubeMap.h"
#include "Camera.h"

void SkySphere::Build()
{
	renderer = AddInternalChildEntity<MeshRenderer>();
	renderer->name = "renderer";
}

void SkySphere::Init()
{
	

	renderer->SetMesh( ShadowEngine::Assets::Mesh::CreateSphere(0, 0));
	
	auto m_Shader = ShadowEngine::Ref<ShadowEngine::Rendering::Shader>(ShadowEngine::Rendering::Shader::CreateFromCompiled("Shaders/SkyBox-VS.cso", "Shaders/SkyBox-FS.cso"));

	auto m_Material = std::make_shared<ShadowEngine::Assets::Material>(m_Shader);

	auto env_map = std::make_shared<ShadowEngine::Assets::TextureCubeMap>("./Resources/Textures/cube_maps/ame_ash/ashcanyon.tga");
	env_map->Upload();
	m_Material->SetTexture("Mat_Env", env_map);
	m_Material->SetProperty("tint", glm::vec4(1, 1, 1, 1));

	m_Material->UpdateBufferIfDirty();

	renderer->SetMaterial(m_Material);
	renderer->SetScale({ 2,2,2 });
	renderer->SetPosition({0,0,0});
}

void SkySphere::Update(float dt)
{
	renderer->SetPosition(scene->mainCamera->parent->GetTransform()->GetPosition());
}
