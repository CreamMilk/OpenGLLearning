#pragma once

#include <vector>

namespace OpenGLLens
{
	struct VertexBufferElement
	{
		unsigned int type;
		unsigned int count;
		unsigned char normalized;

		static unsigned int getSizeOfType(unsigned int type)
		{
			switch (type)
			{
			case 0x1400: // GL_BYTE
			case 0x1401: // GL_UNSIGNED_BYTE
				return 1;
			case 0x1402: // GL_SHORT
			case 0x1403: // GL_UNSIGNED_SHORT
				return 2;
			case 0x1404: // GL_INT
			case 0x1405: // GL_UNSIGNED_INT
			case 0x1406: // GL_FLOAT
				return 4;
			case 0x140A: // GL_DOUBLE
				return 8;
			default:
				return 0;
			}
		}
	};
	class VertexBufferLayout
	{
	public:
		VertexBufferLayout()
			:m_stride(0) {
		};

		template<typename T>
		void push(unsigned int count)
		{
			static_assert(false);
		}

		template<>
		void push<float>(unsigned int count)
		{
			m_elements.push_back({ 0x1406, count, false }); // GL_FLOAT
			m_stride += count * VertexBufferElement::getSizeOfType(0x1406);
		}

		template<>
		void push<unsigned int>(unsigned int count)
		{
			m_elements.push_back({ 0x1405, count, false }); // GL_UNSIGNED_INT
			m_stride += count * VertexBufferElement::getSizeOfType(0x1405);
		}

		template<>
		void push<unsigned char>(unsigned int count)
		{
			m_elements.push_back({ 0x1401, count, true }); // GL_UNSIGNED_BYTE
			m_stride += count * VertexBufferElement::getSizeOfType(0x1401);
		}

		inline const std::vector<VertexBufferElement>& getElements() const { return m_elements; }

		inline unsigned int getStride() const { return m_stride; }
	private:
		std::vector<VertexBufferElement> m_elements;
		unsigned int m_stride;

	};
}


