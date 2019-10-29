#pragma once


#include "ShadowRenderer/ConstantBuffer.h"
#include "DataStructs.h"

namespace ShadowEngine::Rendering
{
	class RenderNode
	{
		ConstantBuffer_Typed<ModelData> modelDataCB;
		Ref<Assets::Mesh> mesh;
		Ref<Assets::Material> mat;

	public:
		RenderNode(Ref<Assets::Mesh> mesh, Ref<Assets::Material> material);

		Ref<Assets::Mesh> GetMesh();

		Ref<Assets::Material> GetMaterial();

		ConstantBuffer_Typed<ModelData> GetCB();

		void UpdateTransform(glm::mat4x4 trans);
	};
	
	class RenderScene
	{
		using RenderNodeList = std::vector<Ref<RenderNode>>;
		
		RenderNodeList nodes;

	public:
		size_t GetNodeCount();

		Ref<RenderNode> AddRenderNode(Ref<Assets::Mesh> mesh, Ref<Assets::Material> material);


		using iterator = RenderNodeList::iterator;
		using const_iterator = RenderNodeList::const_iterator;
		
		iterator begin() { return nodes.begin(); }
		iterator end() { return nodes.end(); }
		const_iterator begin() const { return nodes.begin(); }
		const_iterator end() const { return nodes.end(); }
		const_iterator cbegin() const { return nodes.cbegin(); }
		const_iterator cend() const { return nodes.cend(); }



	};
}
