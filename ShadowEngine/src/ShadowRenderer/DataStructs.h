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
		 */
		static BufferLayout input_layout;

		Vertex(glm::vec3 pos) :pos(pos), normal({ 0,0,0 }), uv({ 0,0 }), color({ 0,0,0,0 })
		{}

		Vertex(glm::vec3 pos, glm::vec3 normal, glm::vec2 uv, glm::vec4 color) :pos(pos), normal(normal), uv(uv), color(color)
		{}

		Vertex() :pos({0,0,0}), normal({ 0,0,0 }), uv({ 0,0 }), color({ 0,0,0,0 })
		{}
	};

	struct ModelData
	{
		glm::mat4x4 modelToWorld;
	};

	struct LightData
	{
		UINT type; glm::vec3 pos;

		glm::vec3 dir; float pad5;

		glm::vec4 ambient;

		glm::vec4 diffuse;

		glm::vec3 att; 

		float range;
	};

	struct WorldData {
		glm::mat4x4 viewProjection;
		glm::mat4x4 rayDir;
		glm::vec4 cameraPos;

		LightData lights[5];
	};
}
