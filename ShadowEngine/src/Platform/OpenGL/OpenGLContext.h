#pragma once


#include "SDL2/SDL.h"
#include "ShadowRenderer/GraphicsContext.h"

namespace ShadowEngine::Rendering::OpenGL {

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
