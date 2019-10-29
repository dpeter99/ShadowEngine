#include "shpch.h"
#include "ShadowRenderer/RenderScene.h"

namespace ShadowEngine::Rendering {
	RenderNode::RenderNode(Ref<Assets::Mesh> mesh, Ref<Assets::Material> material)
	{
		this->mesh = mesh;
		this->mat = material;
	}

	Ref<Assets::Mesh> RenderNode::GetMesh()
	{
		return mesh;
	}

	Ref<Assets::Material> RenderNode::GetMaterial()
	{
		return mat;
	}

	ConstantBuffer_Typed<ModelData> RenderNode::GetCB()
	{
		return modelDataCB;
	}

	void RenderNode::UpdateTransform(glm::mat4x4 trans)
	{
		modelDataCB->modelToWorld = trans;
		modelDataCB.Upload();
	}

	Ref<RenderNode> RenderScene::AddRenderNode(
		Ref<Assets::Mesh> mesh, Ref<Assets::Material> material)
	{
		auto node = std::make_shared<RenderNode>(mesh, material);

		nodes.push_back(node);

		return node;
	}
}