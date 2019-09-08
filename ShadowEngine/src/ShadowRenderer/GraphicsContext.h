#pragma once
#include "RendererAPI.h"


namespace ShadowRenderer {

	class GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

		static GraphicsContext* Create(SDL_Window* window);
	};

	
}
