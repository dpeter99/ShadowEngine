#pragma once
#include "Core/Core.h"
#include "Core/SHObject.h"
#include "ShadowAsset/ShadowAsset.h"

#include "ShadowRenderer/Buffer.h"

namespace ShadowEngine::Assets {

	class Mesh : public ShadowAsset
	{
		SHObject_Base(Mesh)

	public:
		/**
		 * \brief The index buffer used 
		 */
		Ref<Rendering::IndexBuffer> index_buffer;
		Ref<Rendering::VertexBuffer> vertex_buffer;

		Mesh(void* data, unsigned int sizeInBytes, unsigned int stride,
			uint32_t* indexData, unsigned int indexDataSizeInBytes);
	};
}