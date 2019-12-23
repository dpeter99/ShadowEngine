#include "shpch.h"

#include "DirectionalLight.h"
#include "iostream"
#include <ShadowRenderer\Renderer.h>

void DirectionalLight::Init()
{


	node = ShadowEngine::Rendering::Renderer::AddLightNode();

	UpdateRenderNode();
}

void DirectionalLight::TransformChanged()
{
	if (node.get() != nullptr)
		UpdateRenderNode();
}

void DirectionalLight::UpdateRenderNode()
{
	node->type = ShadowEngine::Rendering::LightType::Directional;
	node->ambient = ambient;
	node->diffuse = diffuse;
	node->dir = direction;
}

