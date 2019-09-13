#pragma once
#include "Inspector/Inspector.h"
#include "imgui.h"
#include "Inspector/InspectorSystem.h"
#include "ShadowInput/Bindings/BindingAND.h"
#include "ShadowInput/Bindings/BindingOR.h"

namespace ShadowEngine::InputSystem
{

	class BindingORInspector :
		public Debug::Inspector

	{
		SHObject_Base(BindingORInspector)


	public:
		void Draw(SHObject& obj) override
		{
			auto& binding_and = dynamic_cast<BindingOR<bool>&>(obj);
			//ImGui::Text("-");

			
			if (ImGui::TreeNode(&obj,"Binding AND")) {
				ImGui::Text("A binding: A: %d, B: %d", binding_and.aState, binding_and.bState);
				Debug::InspectorSystem::DrawSub(binding_and.GetABinding());

				ImGui::Text("B binding:");
				Debug::InspectorSystem::DrawSub(binding_and.GetBBinding());
				ImGui::TreePop();
			}
			
			ImGui::Indent();
			for (int i = 0; i < binding_and.ModifierCount(); ++i)
			{
				Debug::InspectorSystem::DrawSub(binding_and.GetModifier(i));
			}
			ImGui::Unindent();


		}
	};

}

