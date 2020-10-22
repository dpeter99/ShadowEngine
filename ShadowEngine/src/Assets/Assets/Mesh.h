#pragma once
#include "Core/Core.h"
#include "Core/SHObject.h"
#include "Assets/ShadowAsset.h"

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

		/*Mesh(void* data, unsigned int sizeInBytes, unsigned int stride,
			uint32_t* indexData, unsigned int indexDataSizeInBytes);*/

		Mesh(std::vector<Rendering::Vertex> vertices, std::vector<uint32_t> indexData);

		static Ref<Mesh> LoadModel_obj(const std::string& filePath);

		static Ref<Mesh> CreateSphere(int LatLines, int LongLines);
		static Ref<Mesh> CreateInverseSphere(int LatLines, int LongLines);

		void Load(SFF::SFFElement& root, Assets::FileSystem::Path path) override;

		void SetName(std::string name) override;
	};
}
