#include "VertexArray.h"

#include <glad/glad.h>
#include <assert.h>

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace OpenGLLens
{
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_vaoId);
	}

	VertexArray::~VertexArray()
	{
		if (m_vaoId != 0)
		{
			glDeleteVertexArrays(1, &m_vaoId);
			m_vaoId = 0;
		}
		
	}

	bool VertexArray::bind() const
	{
		if (m_vaoId != 0)
		{
			glBindVertexArray(m_vaoId);
			return true;
		}
		else
		{
			assert(false);
			return false;
		}
	}

	void VertexArray::unbind() const
	{
		if(m_vaoId != 0)
		{
			glBindVertexArray(0);
		}
		else
		{
			assert(false);
		}
	}

	void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
	{
		if (bind() && vb.bind())
		{
			const auto& elements = layout.getElements();
			unsigned int offset = 0;
			for (unsigned int i = 0; i < elements.size(); i++)
			{
				const auto& element = elements[i];
				glEnableVertexAttribArray(i);
				glVertexAttribPointer(i, element.count, element.type,
					element.normalized, layout.getStride(), (const void*)offset);

				offset += element.count * VertexBufferElement::getSizeOfType(element.type);
			}
		}
	}
}