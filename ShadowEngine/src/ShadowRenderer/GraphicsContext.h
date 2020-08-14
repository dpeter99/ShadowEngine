#pragma once
#include <SDL.h>

class ShadowWindow;

namespace ShadowEngine::Rendering {

	/// <summary>
	/// Represents the context that is being used to render in. This means things like the window and the output buffer.
	/// This should be implemented by each renderer back-end to store what it needs.
	/// </summary>
	class GraphicsContext
	{
	public:
		virtual ~GraphicsContext() = default;
		
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

		static Ref<GraphicsContext> Create(ShadowWindow* window);
	};	
}
