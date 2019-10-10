#pragma once
#include "Core/Core.h"
#include <glm/glm.hpp>

struct Vertex
{
	glm::vec3 pos;
	glm::vec3 normal;
	glm::vec2 uv;

	glm::vec4 color;
};
