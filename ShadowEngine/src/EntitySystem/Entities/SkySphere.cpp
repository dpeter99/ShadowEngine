#include "shpch.h"
#include "SkySphere.h"
#include "EntitySystem/Scene.h"
#include "Assets/Assets/Textures/TextureCubeMap.h"
#include "Camera.h"
#include <Assets\AssetManager.h>

void SkySphere::Build()
{
	renderer = AddInternalChildEntity<MeshRenderer>();
	renderer->name = "renderer";
}

void SkySphere::Init()
{
	auto assetManager = ShadowEngine::Assets::AssetManager::getInstance();

	renderer->SetMesh( ShadowEngine::Assets::Mesh::CreateSphere(0, 0));
	
	//auto m_Shader = ShadowEngine::Ref<ShadowEngine::Rendering::Shader>(ShadowEngine::Rendering::Shader::CreateFromCompiled("Shaders/SkyBox-VS.cso", "Shaders/SkyBox-FS.cso"));
	auto shader = assetManager->GetAsset<ShadowEngine::Rendering::Shader>("demo:/shaders/skybox/skybox.sff");


	auto m_Material = std::make_shared<ShadowEngine::Assets::Material>(shader);

	

	auto env_map = assetManager->GetAsset<ShadowEngine::Assets::TextureCubeMap>({ "demo:/textures/cube_maps/ame_ash/ashcanyon.sff" });
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
