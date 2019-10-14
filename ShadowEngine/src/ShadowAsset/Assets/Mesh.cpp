#include "shpch.h"
#include "Mesh.h"

namespace ShadowEngine::Assets {


	Mesh::Mesh(void* vertices, unsigned sizeInBytes, unsigned stride, uint32_t* indexData,
		unsigned indexDataSizeInBytes)
	{
		//vertex_buffer.reset(ShadowEngine::Rendering::VertexBuffer::Create(vertices, sizeInBytes));
		//vertex_buffer.reset(ShadowEngine::Rendering::IndexBuffer::Create(indexData, indexDataSizeInBytes));
	}

}