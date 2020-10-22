#include "RendererInfo.h"

#include "imgui.h"

#include "ShadowModules/ShadowModuleManager.h"

#include "ShadowRenderer/Renderer.h"
#include "Platform/D3D12/DX12RendererAPI.h"

#include "ImGui/IconsFontAwesome5.h"
#include <string>

namespace ShadowLight::Editor {


	void RendererInfo::Draw()
	{
		if (renderer == nullptr) {
			auto* mm = ShadowEngine::ShadowModuleManager::instance;
			renderer = mm->GetModuleByType<ShadowEngine::Rendering::Renderer>();
		}
		
		ImGui::Begin("Renderer", &active, ImGuiWindowFlags_None);

		this->D3D12Inspector();
		

		ImGui::End();

	}

	void RendererInfo::D3D12Inspector()
	{
		if(d3d12Renderer == nullptr)
		{
			d3d12Renderer = (ShadowEngine::Rendering::D3D12::DX12RendererAPI*)renderer->instance->GetRendererAPI();
		}
		
		if (!ImGui::CollapsingHeader("D3D12"))
			return;

		if(ImGui::TreeNode("Command Allocators"))
		{
			auto pool = d3d12Renderer->command_allocator_pool;
			for(auto& list : pool->GetAllAllocaotrs())
			{
				for(auto& allocator : list.second)
				{
					std::string text = "";
					text += std::to_string( allocator->GetID());

					switch (allocator->GetType())
					{
					case 0:
						text += " Direct";
						break;
					case 1:
						text += " BUNDLE";
						break;
					case 2:
						text += " COMPUTE";
						break;
					case 3:
						text += " COPY";
						break;

					default:
						break;
					}

					ImGui::Text(text.c_str());
				}
			}

			ImGui::TreePop();
		}

	}

}
