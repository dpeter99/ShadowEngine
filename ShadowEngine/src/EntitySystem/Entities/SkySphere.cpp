#include "shpch.h"
#include "SkySphere.h"
#include "EntitySystem/ShadowScene.h"
#include "ShadowAsset/Assets/Textures/TextureCubeMap.h"

void SkySphere::Init()
{
	renderer = scene->AddEntity<MeshRenderer>();

	renderer->SetMesh( ShadowEngine::Assets::Mesh::CreateSphere(0, 0));
	
	auto m_Shader = ShadowEngine::Ref<ShadowEngine::Rendering::Shader>(ShadowEngine::Rendering::Shader::CreateFromCompiled("Shaders/SkyBox-VS.cso", "Shaders/SkyBox-FS.cso"));

	auto m_Material = std::make_shared<ShadowEngine::Assets::Material>(m_Shader);

	auto env_map = std::make_shared<ShadowEngine::Assets::TextureCubeMap>("./Resources/Textures/giraffe.png");
	env_map->Upload();
	m_Material->SetTexture("Mat_Env", env_map);
	m_Material->SetProperty("tint", glm::vec4(1, 1, 1, 1));

	m_Material->UpdateBufferIfDirty();

	renderer->SetMaterial(m_Material);
	renderer->transform.SetScale({ 5,5,5 });
}
