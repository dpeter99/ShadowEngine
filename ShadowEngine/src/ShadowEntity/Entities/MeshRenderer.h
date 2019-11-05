#pragma once
#include "ShadowEntity/SceneEntity.h"
#include "ShadowAsset/Assets/Mesh.h"
#include "ShadowAsset/Assets/Material.h"
#include "ShadowRenderer/RenderScene.h"

class MeshRenderer:
	public ShadowEngine::ShadowEntity::SceneEntity
{
	SHObject_Base(MeshRenderer)
	Entity_Base(MeshRenderer, ShadowEngine::ShadowEntity::SceneEntity)

private:
	ShadowEngine::Ref<ShadowEngine::Assets::Mesh> mesh;
	ShadowEngine::Ref<ShadowEngine::Assets::Material> mat;

	ShadowEngine::Ref<ShadowEngine::Rendering::RenderNode> node;
	
public:
	void Init() override;
	ShadowEngine::ShadowEntity::EntityFlags GetFlags() override { return ShadowEngine::ShadowEntity::EntityFlags::NONE; };

	void SetMesh(ShadowEngine::Ref<ShadowEngine::Assets::Mesh> m) { mesh = m; };
	ShadowEngine::Ref<ShadowEngine::Assets::Mesh> GetMesh() { return  mesh; };
	
	void SetMaterial(ShadowEngine::Ref<ShadowEngine::Assets::Material> m) { mat = m; };
	ShadowEngine::Ref<ShadowEngine::Assets::Material> SetMaterial() { return mat; };
	
private:
	void TransformChanged() override;;

	void UpdateRenderNode();

};

