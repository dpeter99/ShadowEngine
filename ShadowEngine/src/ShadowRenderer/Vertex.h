#pragma once
#include "Core/Core.h"
#include <glm/glm.hpp>
#include "Buffer.h"

namespace ShadowEngine::Rendering {

	struct Vertex
	{
		glm::vec3 pos;
		glm::vec3 normal;
		glm::vec2 uv;

		glm::vec4 color;

		/**
		 * \brief The default layout of the meshes being used
		 * TODO: Move this to global Renderer
		 */
		static BufferLayout input_layout;
	};

}
