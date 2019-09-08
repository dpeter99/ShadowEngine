#include "shpch.h"
#include "OpenGLContext.h"

//#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace ShadowRenderer {

	OpenGLContext::OpenGLContext(SDL_Window* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		SH_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		//TODO: port to SDL2

		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

		SDL_GL_CreateContext(m_WindowHandle);

		printf("OpenGL loaded\n");
		int status = gladLoadGLLoader(SDL_GL_GetProcAddress);
		SH_CORE_ASSERT(status, "Failed to initialize Glad!");

		SH_CORE_INFO("OpenGL Info:");
		SH_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		SH_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		SH_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

	}

	void OpenGLContext::SwapBuffers()
	{
		//glfwSwapBuffers(m_WindowHandle);
		SDL_GL_SwapWindow(m_WindowHandle);
	}

}