#pragma once

#include "Log.h"
#include "Core/Core.h"

namespace ShadowEngine::Rendering {


	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:    return 4;
			case ShaderDataType::Float2:   return 4 * 2;
			case ShaderDataType::Float3:   return 4 * 3;
			case ShaderDataType::Float4:   return 4 * 4;
			case ShaderDataType::Mat3:     return 4 * 3 * 3;
			case ShaderDataType::Mat4:     return 4 * 4 * 4;
			case ShaderDataType::Int:      return 4;
			case ShaderDataType::Int2:     return 4 * 2;
			case ShaderDataType::Int3:     return 4 * 3;
			case ShaderDataType::Int4:     return 4 * 4;
			case ShaderDataType::Bool:     return 1;
		}

		SH_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	/// <summary>
	/// This represents a single filed in a vertex buffer layout
	/// </summary>
	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		uint32_t Offset;
		bool Normalized;

		BufferElement() : Name(""), Type(ShaderDataType::Float),Size(0),Offset(0),Normalized(false)
		{}

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{
		}

		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
				case ShaderDataType::Float:   return 1;
				case ShaderDataType::Float2:  return 2;
				case ShaderDataType::Float3:  return 3;
				case ShaderDataType::Float4:  return 4;
				case ShaderDataType::Mat3:    return 3 * 3;
				case ShaderDataType::Mat4:    return 4 * 4;
				case ShaderDataType::Int:     return 1;
				case ShaderDataType::Int2:    return 2;
				case ShaderDataType::Int3:    return 3;
				case ShaderDataType::Int4:    return 4;
				case ShaderDataType::Bool:    return 1;
			}

			SH_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	};

	/// <summary>
	/// This class stores the layout of a Vertex buffer (pos, uv, color, etc..)
	/// This is used by the graphics api to generate the platform specific description of the vertex buffer.
	/// Each field in the Layout is stored in a BufferElement. These can be retrived by calling <code>BufferLayout.GetElements()</code>
	/// 
	/// 
	/// The vertex buffers layout can be retrived by calling: <code>VertexBuffer.GetLayout()</code>
	/// 
	/// </summary>
	class BufferLayout
	{
	public:
		BufferLayout() {}

		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_Elements(elements)
		{
			CalculateOffsetsAndStride();
		}

		inline uint32_t GetStride() const { return m_Stride; }
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	private:
		void CalculateOffsetsAndStride()
		{
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}
	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};

	/// <summary>
	/// This is the base class for Vertex Buffers
	/// These are used in a Mesh to store the point data
	/// 
	/// These need to be implemented by the actual graphics api (D3D12)
	/// The render api agnostic parts can use this class to refer to the actual objects.
	/// </summary>
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		//virtual void Bind() const = 0;
		//virtual void Unbind() const = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		static VertexBuffer* Create(void* vertices, uint32_t size);
	};

	/// <summary>
	/// This is the base class for Index Buffers
	/// These are used in a Mesh to store the point triangle data
	/// 
	/// These need to be implemented by the actual graphics api (D3D12)
	/// The render api agnostic parts can use this class to refer to the actual objects.
	/// </summary>
	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		//virtual void Bind() const = 0;
		//virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t size);
	};

}
