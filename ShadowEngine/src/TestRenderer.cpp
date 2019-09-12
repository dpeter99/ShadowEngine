#include "shpch.h"
#include "TestRenderer.h"
#include "ShadowRenderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/gtx/quaternion.hpp>

TestRenderer::TestRenderer() : m_CameraPosition(0.0f) {

	m_VertexArray.reset(ShadowRenderer::VertexArray::Create());

	float vertices[3 * 7] = {
		-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
		 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
	};

	ShadowEngine::Ref<ShadowRenderer::VertexBuffer> vertexBuffer;
	vertexBuffer.reset(ShadowRenderer::VertexBuffer::Create(vertices, sizeof(vertices)));
	ShadowRenderer::BufferLayout layout = {
		{ ShadowRenderer::ShaderDataType::Float3, "a_Position" },
		{ ShadowRenderer::ShaderDataType::Float4, "a_Color" }
	};
	vertexBuffer->SetLayout(layout);
	m_VertexArray->AddVertexBuffer(vertexBuffer);

	uint32_t indices[3] = { 0, 1, 2 };
	ShadowEngine::Ref<ShadowRenderer::IndexBuffer> indexBuffer;
	indexBuffer.reset(ShadowRenderer::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
	m_VertexArray->SetIndexBuffer(indexBuffer);

	m_SquareVA.reset(ShadowRenderer::VertexArray::Create());

	float squareVertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
	};

	ShadowEngine::Ref<ShadowRenderer::VertexBuffer> squareVB;
	squareVB.reset(ShadowRenderer::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
	squareVB->SetLayout({
		{ ShadowRenderer::ShaderDataType::Float3, "a_Position" },
		{ ShadowRenderer::ShaderDataType::Float2, "a_TexCoord" }
		});
	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	ShadowEngine::Ref<ShadowRenderer::IndexBuffer> squareIB;
	squareIB.reset(ShadowRenderer::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
	m_SquareVA->SetIndexBuffer(squareIB);

	std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

	std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

	m_Shader.reset(ShadowRenderer::Shader::Create(vertexSrc, fragmentSrc));

	std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

	std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			
			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

	m_FlatColorShader.reset(ShadowRenderer::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));

	std::string textureShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;

			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

	std::string textureShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec2 v_TexCoord;
			
			uniform sampler2D u_Texture;

			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";

	m_TextureShader.reset(ShadowRenderer::Shader::Create(textureShaderVertexSrc, textureShaderFragmentSrc));

	m_Texture = ShadowRenderer::Texture2D::Create("Resources/Textures/Checkerboard.png");
	m_ChernoLogoTexture = ShadowRenderer::Texture2D::Create("Resources/Textures/ChernoLogo.png");

	std::dynamic_pointer_cast<ShadowRenderer::OpenGLShader>(m_TextureShader)->Bind();
	std::dynamic_pointer_cast<ShadowRenderer::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);

}

void TestRenderer::Update() {

	//m_Camera.transform.SetPosition(m_CameraPosition);
	//m_Camera.transform.SetRotation(glm::quat(glm::vec3(0,m_CameraRotation,0)));

	//ShadowRenderer::Renderer::BeginScene(m_Camera);

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	std::dynamic_pointer_cast<ShadowRenderer::OpenGLShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<ShadowRenderer::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
			ShadowRenderer::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
		}
	}

	m_Texture->Bind();
	ShadowRenderer::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
	m_ChernoLogoTexture->Bind();
	ShadowRenderer::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));


	// Triangle
	// Hazel::Renderer::Submit(m_Shader, m_VertexArray);

}