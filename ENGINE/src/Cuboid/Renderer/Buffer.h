#ifndef CUBOID_RENDERER_BUFFER_H
#define CUBOID_RENDERER_BUFFER_H

#include <string>
#include <vector>

#include "Cuboid/Core/Core.h"

namespace Cuboid
{
	class Shader;


	enum class ShaderDataType
	{ 

		None = 0, Float1, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool, Byte4
	
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float1:   return 4;
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
			case ShaderDataType::Byte4:	   return 4;
		}

		return 0;
	}

	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		uint32_t Offset;
		bool Normalized;

		BufferElement() = default;

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
				: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{
		}

		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
				case ShaderDataType::Float1:   return 1;
				case ShaderDataType::Float2:  return 2;
				case ShaderDataType::Float3:  return 3;
				case ShaderDataType::Float4:  return 4;
				case ShaderDataType::Mat3:    return 3; // 3* float3
				case ShaderDataType::Mat4:    return 4; // 4* float4
				case ShaderDataType::Int:     return 1;
				case ShaderDataType::Int2:    return 2;
				case ShaderDataType::Int3:    return 3;
				case ShaderDataType::Int4:    return 4;
				case ShaderDataType::Bool:    return 1;
				case ShaderDataType::Byte4: return 4;
			}

			return 0;
		}
	};

	class BufferLayout
	{
		public:
		BufferLayout() {}

		BufferLayout(const std::initializer_list<BufferElement>& elements)
				: m_Elements(elements)
		{
			CalculateOffsetsAndStride();
		}

		uint32_t GetStride() const { return m_Stride; }
		const std::vector<BufferElement>& GetElements() const { return m_Elements; }

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


	class IndexBuffer
	{
	public:
		virtual void Bind() const = 0;

		virtual void UnBind() const = 0;

		static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t count);

		virtual uint32_t GetCount() const = 0;

		virtual ~IndexBuffer() = default;
	};


	class VertexBuffer
	{
		public:
			virtual void Bind() const = 0;

			virtual void UnBind() const = 0;

			virtual void SetLayout(const BufferLayout& layout) = 0;

			virtual void SetData(const void* data, uint32_t size) = 0;

			 virtual void SetShader(const Ref<Shader>& shader) {}

			virtual const BufferLayout& GetBufferLayout() const = 0;

			static Ref<VertexBuffer> Create(void* vertices, uint32_t size);

			static Ref<VertexBuffer> Create(uint32_t size = 0);

			virtual ~VertexBuffer() = default;

	};

}


#endif
