#include "shpch.h"
#include "Mesh.h"
#include <assimp\Importer.hpp>

namespace ShadowEngine::Assets {


	Mesh::Mesh(void* vertices, unsigned sizeInBytes, unsigned stride, uint32_t* indexData,
		unsigned indexDataSizeInBytes)
	{
		vertex_buffer.reset(ShadowEngine::Rendering::VertexBuffer::Create(vertices, sizeInBytes));
		index_buffer.reset(ShadowEngine::Rendering::IndexBuffer::Create(indexData, indexDataSizeInBytes));
	}
	void A() {
		std::string path = "../Media/" + filePath;

		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_GenUVCoords);

		//ASSERT(scene != nullptr, "Failed to load obj file: '%s'. Assimp error message: '%s'", path.c_str(), importer.GetErrorString());

		//ASSERT(scene->HasMeshes(), "Obj file: '%s' does not contain a mesh.", path.c_str());

		// for this example we only load the first mesh
		const aiMesh* mesh = scene->mMeshes[0];

		std::vector<unsigned int> indices;
		std::vector<PNT_Vertex> vertices;
		indices.reserve(mesh->mNumFaces);
		vertices.reserve(mesh->mNumVertices);

		PNT_Vertex v;

		for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
			v.position.x = mesh->mVertices[i].x;
			v.position.y = mesh->mVertices[i].y;
			v.position.z = mesh->mVertices[i].z;

			v.normal.x = mesh->mNormals[i].x;
			v.normal.y = mesh->mNormals[i].y;
			v.normal.z = mesh->mNormals[i].z;

			v.tex.x = mesh->mTextureCoords[0][i].x;
			v.tex.y = mesh->mTextureCoords[0][i].y;

			vertices.emplace_back(v);
		}

		for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
			aiFace face = mesh->mFaces[i];
			indices.emplace_back(face.mIndices[0]);
			indices.emplace_back(face.mIndices[1]);
			indices.emplace_back(face.mIndices[2]);
		}

		Egg::Mesh::Geometry::P geometry = Egg::Mesh::IndexedGeometry::Create(device, &(vertices.at(0)), (unsigned int)(vertices.size() * sizeof(PNT_Vertex)), (unsigned int)sizeof(PNT_Vertex),
			&(indices.at(0)), (unsigned int)(indices.size() * 4), DXGI_FORMAT_R32_UINT);

		geometry->AddInputElement({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 });
		geometry->AddInputElement({ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 });
		geometry->AddInputElement({ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 });

		return geometry;

	}
}