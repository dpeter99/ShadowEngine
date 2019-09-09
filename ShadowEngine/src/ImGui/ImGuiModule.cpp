#include "shpch.h"


#include "Core/ShadowApplication.h"
#include "Util/Utility.h"
#include "ShadowEvents/Events/KeyEvents.h"
#include "ShadowEvents/Events/MouseEvents.h"
#include "ShadowEvents/ShadowEventManager.h"
#include "ShadowTime.h"
#include "ShadowEvents/Events/ApplicationEvent.h"

#include "imgui.h"
#include "examples/imgui_impl_sdl.h"
#include "examples/imgui_impl_opengl3.h"

#include "ImGuiModule.h"
#include "SDL2/SDL.h"
#include "Platform/SDL/SDLModule.h"

ImGuiModule* ImGuiModule::instance = nullptr;

void ImGuiModule::Init()
{
	ShadowEventSystem::ShadowEventManager::AddNewEventListener(this);

	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGuiIO& io = ImGui::GetIO();
	io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
	io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
	io.ConfigFlags |= ImGuiConfigFlags_::ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_::ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

	// TEMPORARY: should eventually use ShadowRenderer key codes
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
	
	

	ImGui_ImplSDL2_InitForOpenGL(ShadowApplication::Get().GetWindow().winPtr, SDLModule::GetInstance().GetGlContext());
	ImGui_ImplOpenGL3_Init("#version 410");
}

void ImGuiModule::LateRender()
{	
	
	ImGuiIO& io = ImGui::GetIO();
	/*
	ShadowApplication& app = ShadowApplication::Get();
	io.DisplaySize = ImVec2(app.GetWindow().Width, app.GetWindow().Height);

	float time = Time::deltaTime_ms;
	io.DeltaTime = time;
	*/
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(ShadowApplication::Get().GetWindow().winPtr);
	ImGui::NewFrame();

	for (auto gui_call : guiCalls)
	{
		gui_call->OnGui();
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
		SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
	}
}

void ImGuiModule::OnEvent(ShadowEventSystem::ShadowEvent& e)
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
