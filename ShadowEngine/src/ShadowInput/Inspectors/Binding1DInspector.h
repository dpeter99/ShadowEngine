#pragma once
#include "ShadowInput/IInputBinding.h"
#include "ShadowInput/IShadowAction.h"
#include "Inspector/Inspector.h"
#include "imgui.h"
#include "Inspector/InspectorSystem.h"
#include <SDL2/SDL.h>
#include "ShadowInput/Bindings/Binding1D.h"

namespace ShadowInput {

	class Binding1DInspector :
		public Inspector

	{
		SHObject_Base(Binding1DInspector)


	public:
		void Draw(SHObject& obj) override
		{
			auto& keyboard = dynamic_cast<ShadowInput::Binding1D<bool>&>(obj);
			//ImGui::Text("-");

			
			if (ImGui::TreeNode(&obj,"Binding 1D")) {
				ImGui::Text("Positive binding:");
				InspectorSystem::DrawSub(keyboard.GetPositiveBinding());

				ImGui::Text("Negative binding:");
				InspectorSystem::DrawSub(keyboard.GetPositiveBinding());
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

