#pragma once

#include "EntitySystem/SceneEntity.h"
#include <Inspector\EntityInspector.h>
#include <EntitySystem\Entities\Internal\Inspectors\DefaultInspectors.h>
#include <ShadowRenderer\RenderScene.h>
#include <imgui.h>

class DirectionalLight : public ShadowEngine::EntitySystem::Entity
{
	SHObject_Base(DirectionalLight)
	Entity_Base(DirectionalLight, Entity)
		
	ShadowEngine::Ref<ShadowEngine::Rendering::LightNode> node;
public:
	glm::vec3 direction;
	glm::vec4 ambient;
	glm::vec4 diffuse;

public:
	void Init() override;
	void TransformChanged() override;

	void UpdateRenderNode();
};

class DirectionalLightInspector : public ShadowEngine::Debug::EntityInspector {

public:
	void Draw(ShadowEngine::EntitySystem::rtm_ptr<ShadowEngine::EntitySystem::Entity>& obj) override {

		ShadowEngine::EntitySystem::rtm_ptr<DirectionalLight> light = obj;
		{
			bool changed = false;
			changed |= ImGui::InputFloat3("Direction", &light->direction[0], 0, 2);
			changed |= ImGui::ColorEdit4("Ambient", &light->ambient[0], ImGuiColorEditFlags_Float);
			changed |= ImGui::ColorEdit4("Diffuse", &light->diffuse[0], ImGuiColorEditFlags_Float);
			if (changed)
				light->UpdateRenderNode();
		}
	}
};