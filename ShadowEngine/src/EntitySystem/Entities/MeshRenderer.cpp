#include "shpch.h"
#include "MeshRenderer.h"
#include "ShadowRenderer/Renderer.h"

void MeshRenderer::Init()
{
	node = ShadowEngine::Rendering::Renderer::AddRenderNode(mesh, mat);

	UpdateRenderNode();
}

void MeshRenderer::TransformChanged()
{
	if(node.get() != nullptr)
	UpdateRenderNode();
}

void MeshRenderer::UpdateRenderNode()
{	
	node->GetCB()->modelToWorld = GetWorldTransformMatrix();
	node->GetCB().Upload();
}
