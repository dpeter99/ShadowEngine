#include "shpch.h"
#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "ShadowRenderer/DataStructs.h"
#include "Platform/D3D12/Common.h"

namespace ShadowEngine::Assets {


	Mesh::Mesh(void* vertices, unsigned sizeInBytes, unsigned stride, uint32_t* indexData,
		unsigned indexDataSizeInBytes)
	{
		vertex_buffer.reset(ShadowEngine::Rendering::VertexBuffer::Create(vertices, sizeInBytes));
		index_buffer.reset(ShadowEngine::Rendering::IndexBuffer::Create(indexData, indexDataSizeInBytes));
	}
	
	Ref<Mesh> Mesh::LoadModel_obj(const std::string& filePath) {
		std::string path = "./Resources/Model/" + filePath;

		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_GenUVCoords);

		if (scene == nullptr)
			std::cout << importer.GetErrorString();
		
		SH_ASSERT(scene != nullptr,"Failed to load obj file: '%s'. Assimp error message: '%s'",path.c_str(), importer.GetErrorString());

		ASSERT(scene->HasMeshes(), "Obj file: '%s' does not contain a mesh.", path.c_str());

		// for this example we only load the first mesh
		const aiMesh* mesh = scene->mMeshes[0];

		std::vector<unsigned int> indices;
		std::vector<Rendering::Vertex> vertices;
		indices.reserve(mesh->mNumFaces);
		vertices.reserve(mesh->mNumVertices);

		Rendering::Vertex v;

		for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
			v.pos.x = mesh->mVertices[i].x;
			v.pos.y = mesh->mVertices[i].y;
			v.pos.z = mesh->mVertices[i].z;

			v.normal.x = mesh->mNormals[i].x;
			v.normal.y = mesh->mNormals[i].y;
			v.normal.z = mesh->mNormals[i].z;

			v.uv.x = mesh->mTextureCoords[0][i].x;
			v.uv.y = mesh->mTextureCoords[0][i].y;

			vertices.emplace_back(v);
		}

		for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
			aiFace face = mesh->mFaces[i];
			indices.emplace_back(face.mIndices[0]);
			indices.emplace_back(face.mIndices[1]);
			indices.emplace_back(face.mIndices[2]);
		}


		/*
		Egg::Mesh::Geometry::P geometry = Egg::Mesh::IndexedGeometry::Create(
			device,
			&(vertices.at(0)), (unsigned int)(vertices.size() * sizeof(PNT_Vertex)), (unsigned int)sizeof(PNT_Vertex),
			&(indices.at(0)), (unsigned int)(indices.size() * 4), DXGI_FORMAT_R32_UINT);
		*/

		Ref<Mesh> m = std::make_shared<Mesh>(vertices.data(), vertices.size(), sizeof(Rendering::Vertex),
			indices.data(), indices.size());
		
		return m;

	}
}
