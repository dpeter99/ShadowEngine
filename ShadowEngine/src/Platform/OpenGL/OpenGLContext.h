#pragma once

#include "ShadowRenderer/GraphicsContext.h"

#include "SDL2/SDL.h"

namespace ShadowRenderer {

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(SDL_Window* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		SDL_Window* m_WindowHandle;
	};

}