#pragma once
#include "ShadowModules/ShadowModule.h"
#include <SDL.h>

namespace ShadowEngine::SDLPlatform {

	class SDLModule : public ShadowModule
	{
		SDL_Window* window;
		SDL_GLContext glContext;
		//SDL_Event sdlEvent;

		static SDLModule* instance;

	public:

		static SDLModule& GetInstance() { return *instance; };

		void Init() override;

		void Update() override {};
		void Render() override {};
		void LateRender() override {};

		std::string GetName() override { return "SDLModule"; };

		SDL_GLContext& GetGlContext() { return glContext; };

		SDLModule();
		~SDLModule();
	};
}