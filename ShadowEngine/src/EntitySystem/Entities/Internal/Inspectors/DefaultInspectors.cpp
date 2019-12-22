#include "shpch.h"

#include "DefaultInspectors.h"

#include "imgui.h"



void DrawTransformInspector(ShadowEngine::EntitySystem::rtm_ptr<ShadowEngine::EntitySystem::SceneEntity>& entity) {
	if (ImGui::TreeNodeEx("Transform",ImGuiTreeNodeFlags_DefaultOpen))
	{
		auto pos = entity->GetPosition();
		float vec3_p[3] = { pos.x, pos.y, pos.z};
		if (ImGui::InputFloat3("position", vec3_p)) {
			entity->SetPosition(glm::vec3(vec3_p[0],vec3_p[1],vec3_p[2]));
		}

		auto rot = entity->GetRotation();
		float vec3_r[3] = { rot.x, rot.y, rot.z };
		if (ImGui::InputFloat3("rotation", vec3_r)) {
			entity->SetRotation(glm::vec3(vec3_r[0], vec3_r[1], vec3_r[2]));
		}

		auto size = entity->GetScale();
		float vec3_s[3] = { size.x, size.y, size.z };
		if (ImGui::InputFloat3("size", vec3_s)) {
			entity->SetScale(glm::vec3(vec3_s[0], vec3_s[1], vec3_s[2]));
		}

		ImGui::TreePop();
	}
}