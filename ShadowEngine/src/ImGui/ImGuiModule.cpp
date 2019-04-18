#include "ImGuiModule.h"
#include "SDL2/SDL.h"
#include "imgui.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "ShadowApplication.h"
#include "Utility.h"
#include "ShadowEvents/Events/KeyEvents.h"
#include "ShadowEvents/Events/MouseEvents.h"
#include "ShadowEvents/ShadowEventManager.h"
#include "ShadowTime.h"

ImGuiModule* ImGuiModule::instance = nullptr;

void ImGuiModule::Init()
{
	ShadowEventManager::AddNewEventListener(this);

	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGuiIO& io = ImGui::GetIO();
	io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
	io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

	// TEMPORARY: should eventually use Hazel key codes
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

	ImGui_ImplOpenGL3_Init("#version 410");
}

void ImGuiModule::Update()
{
	ImGuiIO& io = ImGui::GetIO();
	ShadowApplication& app = ShadowApplication::Get();
	io.DisplaySize = ImVec2(app.GetWindow().Width, app.GetWindow().Height);

	float time = Time::deltaTime;
	io.DeltaTime = time;

	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();

	static bool show = true;
	//ImGui::ShowDemoWindow(&show);
	for (auto gui_call : guiCalls)
	{
		gui_call->OnGui();
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiModule::OnEvent(ShadowEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();

	KeyPressedEvent* pressed;
	KeyReleasedEvent* released;

	MouseButtonPressedEvent* buttonPressed;
	MouseButtonReleasedEvent* buttonReleased;
	MouseMovedEvent* moved;

	EVENT_BIND(e,KeyPressedEvent, {
		int key = _event->GetKeyCode();
		io.KeysDown[key] = true;
		return;
	})

	/*if(is<KeyPressedEvent>(e, &pressed))
	{
		int key = pressed->GetKeyCode();
		io.KeysDown[key] = true;
	}

	else*/
	if (is<KeyReleasedEvent>(e, &released))
	{
		int key = released->GetKeyCode();
		io.KeysDown[key] = false;
	}
	else if (is<MouseButtonPressedEvent>(e, &buttonPressed))
	{
		int key = buttonPressed->GetMouseButton();
		if (key == SDL_BUTTON_LEFT) io.MouseDown[0] = true;
		if (key == SDL_BUTTON_RIGHT) io.MouseDown[1] = true;
		if (key == SDL_BUTTON_MIDDLE) io.MouseDown[2] = true;
	}
	else if (is<MouseButtonReleasedEvent>(e, &buttonReleased))
	{
		int key = buttonReleased->GetMouseButton();

		if (key == SDL_BUTTON_LEFT) io.MouseDown[0] = false;
		if (key == SDL_BUTTON_RIGHT) io.MouseDown[1] = false;
		if (key == SDL_BUTTON_MIDDLE) io.MouseDown[2] = false;
	}
	else if (is<MouseMovedEvent>(e, &moved))
	{
		io.MousePos = ImVec2(moved->GetX(), moved->GetY());
	}
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
