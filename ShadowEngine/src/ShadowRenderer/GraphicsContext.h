#pragma once
#include <SDL.h>

class ShadowWindow;

namespace ShadowEngine::Rendering {

	class GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

		static Ref<GraphicsContext> Create(ShadowWindow* window);
	};	
}
