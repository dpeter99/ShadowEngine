#include "shpch.h"

#include "PointLight.h"
#include "iostream"
#include <ShadowRenderer\Renderer.h>

void PointLight::Init()
{


	node = ShadowEngine::Rendering::Renderer::AddLightNode();

	UpdateRenderNode();
}

void PointLight::TransformChanged()
{
	if (node.get() != nullptr)
		UpdateRenderNode();
}

void PointLight::UpdateRenderNode()
{
	node->type = ShadowEngine::Rendering::LightType::Point;
	node->diffuse = diffuse;
	node->pos = this->GetPosition();
	node->attenuation = attenuation;
	node->range = range;
}

