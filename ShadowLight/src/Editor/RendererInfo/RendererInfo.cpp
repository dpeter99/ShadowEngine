#include "RendererInfo.h"

#include "imgui.h"

#include "ShadowModules/ShadowModuleManager.h"

#include "ShadowRenderer/Renderer.h"
#include "Platform/D3D12/DX12RendererAPI.h"

//#include "ImGui/IconsFontAwesome5.h"


namespace ShadowLight::Editor {


	void RendererInfo::Draw()
	{
		if (renderer == nullptr) {
			auto* mm = ShadowEngine::ShadowModuleManager::instance;
			renderer = mm->GetModuleByType<ShadowEngine::Rendering::Renderer>();
		}
		
		ImGui::Begin("Renderer", &active, ImGuiWindowFlags_None);

		
		

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

		if(!ImGui::CollapsingHeader("Command Allocators"))
		{
			auto pool = d3d12Renderer->command_allocaotr_pool;
			for(auto& list : pool->GetAllAllocaotrs())
			{
				for(auto& allocator : list.second)
				{
					std::string text = "";
					text += allocator->GetType();
					ImGui::Text(text.c_str());
				}
			}
		}
	}

}
