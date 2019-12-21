#include "shpch.h"

#include "DefaultInspectors.h"

#include "imgui.h"



void DrawTransformInspector(ShadowEngine::EntitySystem::rtm_ptr<ShadowEngine::EntitySystem::SceneEntity>& entity) {
	if (ImGui::TreeNode("Transform"))
	{
		auto pos = entity->GetPosition();
		float vec3_p[3] = { pos.x, pos.y, pos.z};
		if (ImGui::InputFloat3("position", vec3_p)) {
			entity->SetPosition(glm::vec3(vec3_p[0],vec3_p[1],vec3_p[2]));
		}

		ImGui::TreePop();
	}
}