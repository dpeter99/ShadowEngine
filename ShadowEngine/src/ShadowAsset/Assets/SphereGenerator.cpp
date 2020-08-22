#include "shpch.h"
#include "Mesh.h"
#include "glm/vec3.hpp"
#include "ShadowRenderer/DataStructs.h"
#include <map>

namespace ShadowEngine::Assets {

	struct TriangleIndices
	{
	public:
		int v1;
		int v2;
		int v3;

		TriangleIndices(int v1, int v2, int v3)
		{
			this->v1 = v1;
			this->v2 = v2;
			this->v3 = v3;
		}
	};
	
	glm::vec3 MoveToSphere(glm::vec3 pos)
	{
		double length = glm::sqrt(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z);
		return glm::vec3({ pos.x / length, pos.y / length, pos.z / length });
	}

	Ref<Mesh> Mesh::CreateSphere(int LatLines, int LongLines)
	{
		int recursionLevel = 3;

		std::vector<unsigned int> indices;
		std::vector<Rendering::Vertex> vertices;

		std::map<long, int> middlePointIndexCache;

		int index = 0;

		// create 12 vertices of a icosahedron
		float t = (1.0 + glm::sqrt(5.0)) / 2.0;

		vertices.emplace_back(Rendering::Vertex(MoveToSphere({ -1.0f, t, 0.0f })));
		vertices.emplace_back(Rendering::Vertex(MoveToSphere({ 1.0f, t, 0 })));
		vertices.emplace_back(Rendering::Vertex(MoveToSphere({ -1, -t, 0 })));
		vertices.emplace_back(Rendering::Vertex(MoveToSphere({ 1, -t, 0 })));

		vertices.emplace_back(Rendering::Vertex(MoveToSphere({ 0, -1, t })));
		vertices.emplace_back(Rendering::Vertex(MoveToSphere({ 0, 1, t })));
		vertices.emplace_back(Rendering::Vertex(MoveToSphere({ 0, -1, -t })));
		vertices.emplace_back(Rendering::Vertex(MoveToSphere({ 0, 1, -t })));

		vertices.emplace_back(Rendering::Vertex(MoveToSphere({ t, 0, -1 })));
		vertices.emplace_back(Rendering::Vertex(MoveToSphere({ t, 0, 1 })));
		vertices.emplace_back(Rendering::Vertex(MoveToSphere({ -t, 0, -1 })));
		vertices.emplace_back(Rendering::Vertex(MoveToSphere({ -t, 0, 1 })));

		// create 20 triangles of the icosahedron
		std::list<TriangleIndices> faces;

		// 5 faces around point 0
		faces.push_back(TriangleIndices(0, 11, 5));
		faces.push_back(TriangleIndices(0, 5, 1));
		faces.push_back(TriangleIndices(0, 1, 7));
		faces.push_back(TriangleIndices(0, 7, 10));
		faces.push_back(TriangleIndices(0, 10, 11));

		// 5 adjacent faces 
		faces.push_back(TriangleIndices(1, 5, 9));
		faces.push_back(TriangleIndices(5, 11, 4));
		faces.push_back(TriangleIndices(11, 10, 2));
		faces.push_back(TriangleIndices(10, 7, 6));
		faces.push_back(TriangleIndices(7, 1, 8));

		// 5 faces around point 3
		faces.push_back(TriangleIndices(3, 9, 4));
		faces.push_back(TriangleIndices(3, 4, 2));
		faces.push_back(TriangleIndices(3, 2, 6));
		faces.push_back(TriangleIndices(3, 6, 8));
		faces.push_back(TriangleIndices(3, 8, 9));

		// 5 adjacent faces 
		faces.push_back(TriangleIndices(4, 9, 5));
		faces.push_back(TriangleIndices(2, 4, 11));
		faces.push_back(TriangleIndices(6, 2, 10));
		faces.push_back(TriangleIndices(8, 6, 7));
		faces.push_back(TriangleIndices(9, 8, 1));

		for each (auto& var in faces)
		{
			indices.push_back(var.v1);
			indices.push_back(var.v2);
			indices.push_back(var.v3);
		}
		
		return std::make_shared<Mesh>(vertices.data(), vertices.size(),
									indices.data(), indices.size());
	}


	Ref<Mesh> Mesh::CreateInverseSphere(int LatLines, int LongLines)
	{
		int recursionLevel = 3;

		std::vector<unsigned int> indices;
		std::vector<Rendering::Vertex> vertices;

		std::map<long, int> middlePointIndexCache;

		int index = 0;

		// create 12 vertices of a icosahedron
		float t = (1.0 + glm::sqrt(5.0)) / 2.0;

		vertices.emplace_back(Rendering::Vertex(MoveToSphere({ -1.0f, t, 0.0f })));
		vertices.emplace_back(Rendering::Vertex(MoveToSphere({ 1.0f, t, 0 })));
		vertices.emplace_back(Rendering::Vertex(MoveToSphere({ -1, -t, 0 })));
		vertices.emplace_back(Rendering::Vertex(MoveToSphere({ 1, -t, 0 })));

		vertices.emplace_back(Rendering::Vertex(MoveToSphere({ 0, -1, t })));
		vertices.emplace_back(Rendering::Vertex(MoveToSphere({ 0, 1, t })));
		vertices.emplace_back(Rendering::Vertex(MoveToSphere({ 0, -1, -t })));
		vertices.emplace_back(Rendering::Vertex(MoveToSphere({ 0, 1, -t })));

		vertices.emplace_back(Rendering::Vertex(MoveToSphere({ t, 0, -1 })));
		vertices.emplace_back(Rendering::Vertex(MoveToSphere({ t, 0, 1 })));
		vertices.emplace_back(Rendering::Vertex(MoveToSphere({ -t, 0, -1 })));
		vertices.emplace_back(Rendering::Vertex(MoveToSphere({ -t, 0, 1 })));

		// create 20 triangles of the icosahedron
		std::list<TriangleIndices> faces;

		// 5 faces around point 0
		faces.push_back(TriangleIndices(0, 11, 5));
		faces.push_back(TriangleIndices(0, 5, 1));
		faces.push_back(TriangleIndices(0, 1, 7));
		faces.push_back(TriangleIndices(0, 7, 10));
		faces.push_back(TriangleIndices(0, 10, 11));

		// 5 adjacent faces 
		faces.push_back(TriangleIndices(1, 5, 9));
		faces.push_back(TriangleIndices(5, 11, 4));
		faces.push_back(TriangleIndices(11, 10, 2));
		faces.push_back(TriangleIndices(10, 7, 6));
		faces.push_back(TriangleIndices(7, 1, 8));

		// 5 faces around point 3
		faces.push_back(TriangleIndices(3, 9, 4));
		faces.push_back(TriangleIndices(3, 4, 2));
		faces.push_back(TriangleIndices(3, 2, 6));
		faces.push_back(TriangleIndices(3, 6, 8));
		faces.push_back(TriangleIndices(3, 8, 9));

		// 5 adjacent faces 
		faces.push_back(TriangleIndices(4, 9, 5));
		faces.push_back(TriangleIndices(2, 4, 11));
		faces.push_back(TriangleIndices(6, 2, 10));
		faces.push_back(TriangleIndices(8, 6, 7));
		faces.push_back(TriangleIndices(9, 8, 1));

		for each (auto & var in faces)
		{
			indices.push_back(var.v1);
			indices.push_back(var.v3);
			indices.push_back(var.v2);
		}

		return std::make_shared<Mesh>(vertices.data(), vertices.size(),
			indices.data(), indices.size());
	}

	void Mesh::Load(SFF::SFFElement& root)
	{
	}
}
