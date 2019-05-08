#pragma once
#include "Inspector/Inspector.h"
#include "imgui.h"
#include "Inspector/InspectorSystem.h"
#include "ShadowInput/Bindings/BindingAND.h"

namespace ShadowInput {

	class BindingANDInspector :
		public Inspector

	{
		SHObject_Base(BindingANDInspector)


	public:
		void Draw(SHObject& obj) override
		{
			auto keyboard = dynamic_cast<BindingAND<bool>&>(obj);
			//ImGui::Text("-");

			
			if (ImGui::TreeNode(&obj,"Binding AND")) {
				ImGui::Text("A binding:");
				InspectorSystem::DrawSub(keyboard.GetABinding());

				ImGui::Text("B binding:");
				InspectorSystem::DrawSub(keyboard.GetBBinding());
				ImGui::TreePop();
			}
			
			ImGui::Indent();
			for (int i = 0; i < keyboard.ModifierCount(); ++i)
			{
				InspectorSystem::DrawSub(keyboard.GetModifier(i));
			}
			ImGui::Unindent();


		}
	};

}

