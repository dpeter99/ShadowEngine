#include "shpch.h"
#include "ImGuiModule.h"

#include "Core/ShadowApplication.h"
#include "ShadowEvents/Events/MouseEvents.h"
#include "ShadowEvents/ShadowEventManager.h"

#include "ShadowRenderer/RendererAPI.h"

#include "Platform/D3D12/D3D12RendererAPI.h"

#include "imgui.h"
#include "examples/imgui_impl_sdl.h"
#include "examples/imgui_impl_opengl3.h"
#include "examples/imgui_impl_dx12.h"


#include <SDL.h>
#include "Platform/SDL/SDLModule.h"
#include <ImGui\ImGui_Utils.h>

namespace ShadowEngine::DebugGui {

	ImGuiModule* ImGuiModule::instance = nullptr;

	static ImFont* _fontRegular = nullptr;
	static ImFont* _fontSolid = nullptr;

	void LoadFontAwesome()
	{
		// Loads fonts
		ImGuiIO& io = ImGui::GetIO();
		io.Fonts->AddFontDefault();
		static ImWchar ranges[] = { 0xf000, 0xf82f, 0 };
		ImFontConfig config;
		config.MergeMode = true;
		auto fontRegularPath
			= std::string("./Resources/Fonts/") + FONT_ICON_FILE_NAME_FAR;
		_fontRegular = io.Fonts->AddFontFromFileTTF(fontRegularPath.c_str(),
			ImGui::IconSize, &config, ranges);
		auto fontSolidPath
			= std::string("./Resources/Fonts/") + FONT_ICON_FILE_NAME_FAS;
		_fontSolid = io.Fonts->AddFontFromFileTTF(fontSolidPath.c_str(),
			ImGui::IconSize, &config, ranges);
	}

	void ImGuiModule::Init()
	{
		EventSystem::ShadowEventManager::AddNewEventListener(this);

		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		LoadFontAwesome();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
		io.ConfigFlags |= ImGuiConfigFlags_::ImGuiConfigFlags_DockingEnable;           // Enable Docking
		//io.ConfigFlags |= ImGuiConfigFlags_::ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

		// TEMPORARY: should eventually use ShadowEngine::Rendering key codes
		// Keyboard mapping. ImGui will use those indices to peek into the io.KeysDown[] array.

		io.KeyMap[ImGuiKey_Tab] = SDL_SCANCODE_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = SDL_SCANCODE_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = SDL_SCANCODE_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = SDL_SCANCODE_UP;
		io.KeyMap[ImGuiKey_DownArrow] = SDL_SCANCODE_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = SDL_SCANCODE_PAGEUP;
		io.KeyMap[ImGuiKey_PageDown] = SDL_SCANCODE_PAGEDOWN;
		io.KeyMap[ImGuiKey_Home] = SDL_SCANCODE_HOME;
		io.KeyMap[ImGuiKey_End] = SDL_SCANCODE_END;
		io.KeyMap[ImGuiKey_Insert] = SDL_SCANCODE_INSERT;
		io.KeyMap[ImGuiKey_Delete] = SDL_SCANCODE_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = SDL_SCANCODE_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = SDL_SCANCODE_SPACE;
		io.KeyMap[ImGuiKey_Enter] = SDL_SCANCODE_RETURN;
		io.KeyMap[ImGuiKey_Escape] = SDL_SCANCODE_ESCAPE;
		io.KeyMap[ImGuiKey_A] = SDL_SCANCODE_A;
		io.KeyMap[ImGuiKey_C] = SDL_SCANCODE_C;
		io.KeyMap[ImGuiKey_V] = SDL_SCANCODE_V;
		io.KeyMap[ImGuiKey_X] = SDL_SCANCODE_X;
		io.KeyMap[ImGuiKey_Y] = SDL_SCANCODE_Y;
		io.KeyMap[ImGuiKey_Z] = SDL_SCANCODE_Z;



		ImGui_ImplSDL2_InitForOpenGL(ShadowEngine::ShadowApplication::Get().GetWindow().winPtr, SDLPlatform::SDLModule::GetInstance().GetGlContext());
		

		switch (Rendering::RendererAPI::GetAPI())
		{
		case Rendering::RendererAPI::API::OpenGL:
			ImGui_ImplOpenGL3_Init("#version 410");
			break;
		case Rendering::RendererAPI::API::D3D12:

			auto desc = Rendering::D3D12::D3D12RendererAPI::Instance->descriptorHeap_SRV_CBV->Allocate(1);
			ImGui_ImplDX12_Init(Rendering::D3D12::D3D12RendererAPI::Instance->device.Get(),
								1,
								DXGI_FORMAT_R8G8B8A8_UNORM,
								Rendering::D3D12::D3D12RendererAPI::Instance->descriptorHeap_SRV_CBV->Get().Get(),
								desc.CPU_TableStart,
								desc.GPU_TableStart);
			break;
		default:
			break;
		}
	}

	void ImGuiModule::StartFrame()
	{
		switch (Rendering::RendererAPI::GetAPI())
		{
		case Rendering::RendererAPI::API::OpenGL:
			ImGui_ImplOpenGL3_NewFrame();
			break;
		case Rendering::RendererAPI::API::D3D12:
			ImGui_ImplDX12_NewFrame();
			break;
		default:
			break;
		}

		ImGui_ImplSDL2_NewFrame(ShadowEngine::ShadowApplication::Get().GetWindow().winPtr);

		ImGui::NewFrame();
	}

	void ImGuiModule::OtherWindows()
	{
		ImGuiIO& io = ImGui::GetIO();

		if (Rendering::RendererAPI::GetAPI() == Rendering::RendererAPI::API::OpenGL) {
			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
				SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
			}
		}
		else
		{
			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault(NULL, (void*)(Rendering::D3D12::D3D12RendererAPI::Instance->command_list->GetCommandList().Get()));
			}
		}
	}

	void ImGuiModule::LateRender()
	{

		ImGuiIO& io = ImGui::GetIO();

		for (auto gui_call : guiCalls)
		{
			gui_call->OnGui();
		}

		
		ImGui::Render();

		switch (Rendering::RendererAPI::GetAPI())
		{
		case Rendering::RendererAPI::API::OpenGL:
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			break;
		case Rendering::RendererAPI::API::D3D12:
			ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(),Rendering::D3D12::D3D12RendererAPI::Instance->command_list->GetCommandList().Get());
			break;
		default:
			break;
		}
		
		
	}

	void ImGuiModule::AfterFrameEnd()
	{
		
	}

	void ImGuiModule::OnEvent(EventSystem::ShadowEvent& e)
	{


		ImGui_ImplSDL2_ProcessEvent(e.GetSDLEvnet());

		/*
		ImGuiIO& io = ImGui::GetIO();

		ShadowEventSystem::KeyPressedEvent* pressed;
		ShadowEventSystem::KeyReleasedEvent* released;

		ShadowEventSystem::MouseButtonPressedEvent* buttonPressed;
		ShadowEventSystem::MouseButtonReleasedEvent* buttonReleased;
		ShadowEventSystem::MouseMovedEvent* moved;

		ShadowEventSystem::WindowResizeEvent* resize;

		if(e.GetType() == ShadowEventSystem::KeyPressedEvent::Type())
		{
			ShadowEventSystem::KeyPressedEvent* _event = dynamic_cast<ShadowEventSystem::KeyPressedEvent*>(&e);
			{
				int key = _event->GetKeyCode(); io.KeysDown[key] = true;
				return;
			}
		}
		if (is<ShadowEventSystem::KeyReleasedEvent>(e, &released))
		{
			int key = released->GetKeyCode();
			io.KeysDown[key] = false;
		}
		else if (is<ShadowEventSystem::MouseButtonPressedEvent>(e, &buttonPressed))
		{
			int key = buttonPressed->GetMouseButton();
			if (key == SDL_BUTTON_LEFT) io.MouseDown[0] = true;
			if (key == SDL_BUTTON_RIGHT) io.MouseDown[1] = true;
			if (key == SDL_BUTTON_MIDDLE) io.MouseDown[2] = true;
		}
		else if (is<ShadowEventSystem::MouseButtonReleasedEvent>(e, &buttonReleased))
		{
			int key = buttonReleased->GetMouseButton();

			if (key == SDL_BUTTON_LEFT) io.MouseDown[0] = false;
			if (key == SDL_BUTTON_RIGHT) io.MouseDown[1] = false;
			if (key == SDL_BUTTON_MIDDLE) io.MouseDown[2] = false;
		}
		else if (is<ShadowEventSystem::MouseMovedEvent>(e, &moved))
		{
			io.MousePos = ImVec2(moved->GetX(), moved->GetY());
		}
		else if(is(e, &resize))
		{

		}
		*/
	}



	void ImGuiModule::AddGUICall(IShadowImGui* g)
	{
		instance->guiCalls.emplace_back(g);
	}

	ImGuiModule::ImGuiModule()
	{
		instance = this;
	}


	ImGuiModule::~ImGuiModule()
	{
	}

}