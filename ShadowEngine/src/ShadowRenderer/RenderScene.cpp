#include "shpch.h"
#include "ShadowRenderer/RenderScene.h"

namespace ShadowEngine::Rendering {

	//------------------------------------------
	//Render Node
	//------------------------------------------

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

	ConstantBuffer_Typed<ModelData>& RenderNode::GetCB()
	{
		return modelDataCB;
	}

	void RenderNode::UpdateTransform(glm::mat4x4 trans)
	{
		modelDataCB->modelToWorld = trans;
		modelDataCB.Upload();
	}

	//------------------------------------------
	//Render Scene
	//------------------------------------------

	RenderScene::RenderScene()
	{
		worldData.reset(new ConstantBuffer_Typed<WorldData>());
	}

	Ref<RenderNode> RenderScene::AddRenderNode(
		Ref<Assets::Mesh> mesh, Ref<Assets::Material> material)
	{
		auto node = std::make_shared<RenderNode>(mesh, material);

		nodes.push_back(node);

		return node;
	}

	Ref<LightNode> RenderScene::AddLightNode()
	{
		auto node = std::make_shared<LightNode>();

		LightNodes.push_back(node);

		return node;
	}

	void RenderScene::PrepareWorldData()
	{
		auto cb = worldData.get();
		(*cb)->viewProjection = camera->GetViewProjectionMatrix();

		(*cb)->cameraPos = glm::vec4( camera->GetPosition(),0);

		for (size_t i = 0; i < (LightNodes.size() < 5 ? LightNodes.size() : 5); i++)
		{
			(*cb)->lights[i].type = (UINT)LightNodes[i]->type;
			(*cb)->lights[i].ambient = LightNodes[i]->ambient;
			(*cb)->lights[i].diffuse = LightNodes[i]->diffuse;
			(*cb)->lights[i].dir = glm::vec4( LightNodes[i]->dir,0);

			(*cb)->lights[i].pos = LightNodes[i]->pos;
			(*cb)->lights[i].range = LightNodes[i]->range;
			(*cb)->lights[i].att = LightNodes[i]->attenuation;
		}
		

		cb->Upload();
	}

	Ref<ConstantBuffer_Typed<WorldData>> RenderScene::GetWorldData()
	{
		return worldData;
	}
}