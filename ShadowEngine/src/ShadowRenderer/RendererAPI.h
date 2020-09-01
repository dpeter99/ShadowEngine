#pragma once

#include <glm/glm.hpp>

#include "GraphicsContext.h"
#include "Shader.h"
#include "Assets/Assets/Mesh.h"
#include "Assets/Assets/Material.h"

namespace ShadowEngine::Rendering {


	/// <summary>
	/// Render API abstraction. The render back-ends need to implement this.
	/// We are using a high level abstraction, meaning that we leave as much implementation detail up to the back-end as possible.
	/// These are the calls that the back-end needs to implement, and they will be called from the engine internals.
	/// </summary>
	class RendererAPI
	{
	public:
		/// <summary>
		/// List of the possible back-ends
		/// </summary>
		enum class API
		{
			None = 0,
			OpenGL = 1, //Not implemented
			D3D12 = 2
		};
	public:
		/// <summary>
		/// Initialize the rendering back-end.
		/// </summary>
		/// <param name="ctx">The window context</param>
		virtual void Init(ShadowEngine::Ref<GraphicsContext> ctx) = 0;

		/// <summary>
		/// Sets the default clear color
		///
		/// TODO: This should be a property of the camera like in Unity
		/// </summary>
		/// <param name="color">The color to use as the clear color</param>
		virtual void SetClearColor(const glm::vec4& color) = 0;

		/// <summary>
		/// Clears the screen
		/// </summary>
		virtual void Clear() = 0;


		/// <summary>
		/// Used to issue a render call. This might be a render call recorded into a command list.
		///
		/// TODO: This call should only get a RenderNode so the Renderer can use what it wants.
		/// </summary>
		/// <param name="mesh">The mesh to render</param>
		/// <param name="shader">The shader to use</param>
		/// <param name="materialData">The material data for the shader</param>
		virtual void Draw(const std::shared_ptr<Assets::Mesh>& mesh, const std::shared_ptr<Assets::Material>& shader, const ConstantBuffer& materialData) =0;


		/// <summary>
		/// Marks the start of a render frame. <see cref="Draw">Draw calls</see> will be only called after this.
		/// </summary>
		/// <param name="worldCB">The world data in a Constant buffer</param>
		/// <param name="frame_index">The index of the frame that is bing started</param>
		///
		/// The frame index should never decrease, as it is used for command queue fences.
		virtual  void StartFrame(Ref<ConstantBuffer> worldCB, uint64_t frame_index) = 0;
		

		/// <summary>
		/// Marks the finish of the frame.
		/// </summary>
		virtual void EndFrame() =0;

		virtual void StartResourceUpload() = 0;
		

		inline static API GetAPI() { return s_API; }

		static RendererAPI* RendererAPI::MakeRendererAPI();
	private:
		static API s_API;
	};

}
