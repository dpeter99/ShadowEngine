#pragma once
#include "Core/Core.h"
#include "ShadowModules/ShadowModule.h"

#include "RendererAPI.h"

#include "Shader.h"
#include "ShadowAsset/Assets/Mesh.h"

#include "ShadowRenderer/DataStructs.h"
#include "RenderScene.h"


class Camera;


namespace ShadowEngine::Rendering {
	
	/// <summary>
	/// This is the platform agnostic renderer managger
	/// </summary>
	/// It is used to issue draw calls and build command lists
	/// 
	class Renderer : public ShadowEngine::ShadowModule
	{
		SHObject_Base(Renderer)
		
	private:
		/// <summary>
		/// The underlying renderer api that executes the calls.
		/// </summary>
		/// It currently is a DX12RendererAPI instance
		RendererAPI* s_RendererAPI = nullptr;

		/// <summary>
		/// The Render Scene that represents and holds the data for all items that need to be known for rendering
		/// It holds the: Mesh-Transform-Material combinaations lights and the camera
		/// It is set up with changesin the core update loop and uploaded in the render phase.
		/// </summary>
		RenderScene* scene = nullptr;
		
	public:
		Renderer();

		//Singleton Instance
		static Renderer* instance;

		void Init() override;
		void Update() override;
		void Render() override;
		void LateRender() override {};

		std::string GetName() override { return "Renderer"; }


		/// <summary>
		/// Starts the Rendering scene
		/// Sets up the render API
		/// Sets up the RenderScene for the new frame
		/// 
		/// It gets a Camera Entity pointer witch is used to 
		/// </summary>
		/// <paramref name="camera">The camera that the scene will be rendered from</paramref>
		void BeginScene(Camera* camera);
		
		/// <summary>
		/// Finishes the draw frame recording
		/// After this the render part of the core loop can move forward
		/// </summary>
		void EndScene();

		/// <summary>
		/// Renders all the mesh nodes in the RenderScene
		/// </summary>
		void RenderNodes();
		
		/// <summary>
		/// OLD: Deprecated
		/// Submits a new Mesh to be drawn
		/// </summary>
		/// <param name="mesh">the mesh to be drawn</param>
		/// <param name="shader">the shader to use</param>
		/// <param name="transform">the transform to be applied to the mesh</param>
		static void  Submit  (const Ref<Assets::Mesh> mesh, const Ref<Assets::Material> shader, const glm::mat4& transform = glm::mat4(1.0f));

		/// <summary>
		/// Adds a new render node to the RenderScene
		/// </summary>
		/// <param name="mesh">The mesh to be rendered</param>
		/// <param name="material">The material the render node will have</param>
		/// <param name="transform">The transform compared to the world origin</param>
		/// <returns></returns>
		static Ref<RenderNode> AddRenderNode(const Ref<Assets::Mesh> mesh, const Ref<Assets::Material> material, const glm::mat4& transform = glm::mat4(1.0f));


		/// <summary>
		/// Adds a light node to the RenderScene
		/// </summary>
		/// <returns></returns>
		static Ref<LightNode> AddLightNode();
		

		/// <summary>
		/// Returns the currently selected value of the RenderAPI enum
		/// </summary>
		/// <returns></returns>
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	};


}
