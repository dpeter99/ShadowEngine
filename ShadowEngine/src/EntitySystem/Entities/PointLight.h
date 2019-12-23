#pragma once

#include "EntitySystem/SceneEntity.h"
#include <Inspector\EntityInspector.h>
#include <EntitySystem\Entities\Internal\Inspectors\DefaultInspectors.h>
#include <ShadowRenderer\RenderScene.h>
#include <imgui.h>

class PointLight : public ShadowEngine::EntitySystem::SceneEntity
{
	SHObject_Base(PointLight)
	Entity_Base(PointLight, SceneEntity)
		
	ShadowEngine::Ref<ShadowEngine::Rendering::LightNode> node;
public:

	glm::vec4 diffuse;
	float range;
	glm::vec3 attenuation;

public:
	void Init() override;
	void TransformChanged() override;

	void UpdateRenderNode();
};

class PointLightInspector : public ShadowEngine::Debug::EntityInspector {

public:
	void Draw(ShadowEngine::EntitySystem::rtm_ptr<ShadowEngine::EntitySystem::Entity>& obj) override {

		ShadowEngine::EntitySystem::rtm_ptr<PointLight> light = obj;
		{
			DrawTransformInspector((ShadowEngine::EntitySystem::rtm_ptr<ShadowEngine::EntitySystem::SceneEntity>)obj);

			bool changed = false;
			changed |= ImGui::ColorEdit4("Diffuse", &light->diffuse[0], ImGuiColorEditFlags_Float);
			changed |= ImGui::DragFloat("Range", &light->range,1,0,10);
			changed |= ImGui::DragFloat3("attenuation", &light->attenuation[0],1,0,10);
			if (changed)
				light->UpdateRenderNode();
		}
	}
};