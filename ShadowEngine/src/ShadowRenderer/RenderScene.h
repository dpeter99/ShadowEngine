#pragma once


#include "ShadowRenderer/ConstantBuffer.h"
#include "ShadowAsset/Assets/Textures/TextureCubeMap.h"
#include "DataStructs.h"
#include <EntitySystem\Entities\Camera.h>

namespace ShadowEngine::Rendering
{

	enum class LightType {
		Directional,
		Point,
		Spot
	};

	class LightNode {
	public:
		
		LightType type;
		
		glm::vec3 pos;
		
		glm::vec3 dir;
		
		glm::vec4 ambient;
		glm::vec4 diffuse;

		float range;
		glm::vec3 attenuation;

		LightNode()
		{
			
		}
	};

	class RenderNode
	{
		ConstantBuffer_Typed<ModelData> modelDataCB;
		Ref<Assets::Mesh> mesh;
		Ref<Assets::Material> mat;

	public:
		RenderNode(Ref<Assets::Mesh> mesh, Ref<Assets::Material> material);

		Ref<Assets::Mesh> GetMesh();

		Ref<Assets::Material> GetMaterial();

		ConstantBuffer_Typed<ModelData>& GetCB();

		void UpdateTransform(glm::mat4x4 trans);
	};
	

	///
	///Represents the scene that we are going to render.
	///Constins all of the Render Nodes corrsponding to each mesh we are given
	///Contains all the Light Nodes for each light that we need to use
	///
	class RenderScene
	{
		using RenderNodeList = std::vector<Ref<RenderNode>>;

		//List of all the meshes
		RenderNodeList nodes;

		using LightNodeList = std::vector<Ref<LightNode>>;

		//Lsit of all the lights
		LightNodeList LightNodes;

		Ref<ConstantBuffer_Typed<WorldData>> worldData;

		Camera* camera;

	public:

		RenderScene();
		

		size_t GetNodeCount();

		Ref<RenderNode> AddRenderNode(Ref<Assets::Mesh> mesh, Ref<Assets::Material> material);

		Ref<LightNode> AddLightNode();

		void SetCamera(Camera* c) { camera = c; }

		void PrepareWorldData();

		Ref<ConstantBuffer_Typed<WorldData>> GetWorldData();

		Ref<ShadowEngine::Assets::TextureCubeMap> EnvMap;

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
