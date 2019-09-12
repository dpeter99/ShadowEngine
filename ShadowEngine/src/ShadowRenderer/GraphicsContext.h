#pragma once
#include "RendererAPI.h"
#include "SDL2/SDL.h"

namespace ShadowRenderer {

	class GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

		static GraphicsContext* Create(SDL_Window* window);
	};	
}
