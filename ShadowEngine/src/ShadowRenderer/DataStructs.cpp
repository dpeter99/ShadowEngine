#include "shpch.h"
#include "Buffer.h"
#include "DataStructs.h"

namespace ShadowEngine::Rendering {

	BufferLayout Vertex::input_layout =	{
		{ ShadowEngine::Rendering::ShaderDataType::Float3, "POSITION" },
		{ ShadowEngine::Rendering::ShaderDataType::Float3, "NORMAL" },
		{ ShadowEngine::Rendering::ShaderDataType::Float2, "TEXCOORD" },
		{ ShadowEngine::Rendering::ShaderDataType::Float4, "COLOR" },
	};

}
