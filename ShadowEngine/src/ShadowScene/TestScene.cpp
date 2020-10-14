#include "shpch.h"
#include "TestScene.h"
#include <EntitySystem\Entities\Camera.h>
#include "EntitySystem/Entities/MeshRenderer.h"
#include "EntitySystem/Entities/FirstPersonCamera.h"
#include "Assets/Assets/Textures/Texture.h"
#include "Assets/Assets/Textures/TextureCubeMap.h"
#include "EntitySystem/Entities/SkySphere.h"
#include <EntitySystem\Entities\DirectionalLight.h>
#include <EntitySystem\Entities\PointLight.h>

#include "Assets/Assets/Textures/Texture2D.h"

#include "Assets/AssetManager.h"

#include "ShadowRenderer/Renderer.h"
#include "Platform/D3D12/DX12RendererAPI.h"
#include "Platform/D3D12/Textures/D3D12TextureCubeMap.h"


void TestScene::Init()
{
	//auto c = AddEntity<Camera>();
	//c->SetCameraType(CameraType::Perspective);
	//c->transform.SetPosition({ 0,0.0f,-10.0f });
	
	
	auto fps = AddEntity<FirstPersonCamera>();
	fps->name = "Fps Camera";
	

	auto assetManager = ShadowEngine::Assets::AssetManager::getInstance();
	auto env_map = assetManager->GetAsset<ShadowEngine::Assets::TextureCubeMap>({ "demo:/textures/cube_maps/ame_ash/ashcanyon.sff" });

	auto girafe = assetManager->GetAsset<ShadowEngine::Assets::Texture2D>({ "demo:/textures/models/checker_board.sff" });

	auto api = (ShadowEngine::Rendering::D3D12::DX12RendererAPI*) ShadowEngine::Rendering::Renderer::instance->GetRendererAPI();
	api->UploadResource((ShadowEngine::Rendering::D3D12::D3D12TextureCubeMap*)girafe->getImpl().get());

	api->UploadResource((ShadowEngine::Rendering::D3D12::D3D12TextureCubeMap*)env_map->getImpl().get());
	
	
	
	
	//auto sky = AddEntity<SkySphere>();
	//sky->name = "Sky";
	
	/*
	
	auto env_map = std::make_shared<ShadowEngine::Assets::TextureCubeMap>("./Resources/Textures/cube_maps/ame_ash/ashcanyon.tga");
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
	
	auto sky_light = AddEntity<DirectionalLight>();
	sky_light->name = "Sun light";
	sky_light->direction = { ::cos(270),::sin(25),::sin(270) };
	sky_light->diffuse = { 0.70, 0.80, 1.00,1 };
	sky_light->ambient = { 1.0f, 1.0f, 1.0f, 1.0f };

	auto light = AddEntity<PointLight>();
	light->name = "light";
	light->diffuse = { 1,0,0,1 };
	light->range = 2;
	light->attenuation = { 0.0f, 0.2f, 0.0f };

	*/

	//Scene::Init();
}
