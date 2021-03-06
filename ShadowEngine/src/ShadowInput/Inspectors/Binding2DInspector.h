#pragma once
#include "ShadowInput/IInputBinding.h"
#include "ShadowInput/IShadowAction.h"
#include "Inspector/Inspector.h"
#include "imgui.h"
#include "Inspector/InspectorSystem.h"
#include <SDL.h>
#include "ShadowInput/Bindings/Binding2D.h"

namespace ShadowEngine::InputSystem
{

	class Binding2DInspector :
		public Debug::Inspector

	{
		SHObject_Base(Binding2DInspector)


	public:
		void Draw(SHObject& obj) override
		{
			auto& keyboard = dynamic_cast<Binding2D<bool>&>(obj);			

			if (ImGui::TreeNode(&obj,"Binding 2D")) {

				if (ImGui::TreeNode("X direction")) {
					ImGui::Text("Positive binding:");
					Debug::InspectorSystem::DrawSub(keyboard.GetXPositiveBinding());

					ImGui::Text("Negative binding:");
					Debug::InspectorSystem::DrawSub(keyboard.GetXNegativeBinding());
					ImGui::TreePop();
				}
				if (ImGui::TreeNode("Y direction")) {
					ImGui::Text("Positive binding:");
					Debug::InspectorSystem::DrawSub(keyboard.GetYPositiveBinding());

					ImGui::Text("Negative binding:");
					Debug::InspectorSystem::DrawSub(keyboard.GetYNegativeBinding());
					ImGui::TreePop();
				}
				ImGui::TreePop();
			}
			
			ImGui::Indent();
			for (int i = 0; i < keyboard.ModifierCount(); ++i)
			{
				Debug::InspectorSystem::DrawSub(keyboard.GetModifier(i));
			}
			ImGui::Unindent();

		}
	};

}

