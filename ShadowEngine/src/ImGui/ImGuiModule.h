#pragma once
#include "ShadowModules/ShadowModule.h"
#include "ShadowEvents/IShadowEventListener.h"
#include <list>
#include "IShadowImGui.h"
#include "Platform/D3D12/D3D12DescriptorHeap.h"

namespace ShadowEngine::DebugGui {

	class ImGuiModule :
		public ShadowEngine::ShadowModule, public EventSystem::IShadowEventListener
	{
		SHObject_Base(ImGuiModule)
		
		static ImGuiModule* instance;

		std::list<IShadowImGui*> guiCalls;

		Microsoft::WRL::ComPtr< ID3D12DescriptorHeap> heap;
	public:

		void PreInit() override {};
		void Init() override;
		void Update() override {};
		void Render() override {};
		void LateRender() override;
		void AfterFrameEnd() override;

		void OnEvent(EventSystem::ShadowEvent& e) override;


		static void StartFrame();
		static void OtherWindows();

		Microsoft::WRL::ComPtr< ID3D12DescriptorHeap> GetHeap() { return heap; }
		
		
		std::string GetName() override { return "ImGuiModule"; };

		static void AddGUICall(IShadowImGui* g);

		ImGuiModule();
		~ImGuiModule();
		
	};
}
