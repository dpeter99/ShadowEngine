#pragma once
#include "ShadowInput/IInputBinding.h"
#include "ShadowInput/IShadowAction.h"
#include "Inspector/Inspector.h"
#include "imgui.h"
#include "Inspector/InspectorSystem.h"
#include "ShadowMath/Vector2float.h"

namespace ShadowInput {

	class InputActionInspector :
		public Inspector

	{
		SHObject_Base(InputActionInspector)


	public:
		void Draw(SHObject& obj) override
		{
			auto* action = &dynamic_cast<IShadowAction&>(obj);
			bool actionActive = action->GetPerformed();

			ImGui::Checkbox("", &actionActive);
			ImGui::SameLine(); ImGui::Text("%s %d", action->GetName().c_str(), action->GetState());

			if(action->GetType() == ShadowAction<bool>::Type())
			{
				auto bool_action = dynamic_cast<ShadowAction<bool>*>(action);

				ImGui::AlignTextToFramePadding();
				ImGui::Text("Data:");
				bool data = bool_action->GetData();
				ImGui::SameLine(); ImGui::Checkbox("",&data);
			}
			else if (action->GetType() == ShadowAction<float>::Type())
			{
				auto float_action = dynamic_cast<ShadowAction<float>*>(action);

				ImGui::AlignTextToFramePadding();
				ImGui::Text("Data:");
				float data = float_action->GetData();
				ImGui::SameLine(); ImGui::TextColored(ImVec4(0.5, 0.1, 0.7, 1), "%.2f",data);
			}
			else if (action->GetType() == ShadowAction<ShadowMath::Vector2float>::Type())
			{
				auto float_action = dynamic_cast<ShadowAction<ShadowMath::Vector2float>*>(action);

				ImGui::AlignTextToFramePadding();
				ImGui::Text("Data:");
				float xdata = float_action->GetData().x;
				float ydata = float_action->GetData().y;
				ImGui::SameLine(); ImGui::TextColored(ImVec4(0.5, 0.1, 0.7, 1), "X: %.2f \t Y: %.2f", xdata,ydata);
			}


			auto* binding = &(action->GetBinding());			
			InspectorSystem::DrawSub(*binding);
			

		}
	};

}
