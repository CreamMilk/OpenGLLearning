#include "VertexBuffer.h"
#include <glad/glad.h>

namespace OpenGLLens
{
	VertexBuffer::VertexBuffer(void* data, size_t size)
	{
		glGenBuffers(1, &m_vboId);
		glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	VertexBuffer::~VertexBuffer()
	{
		if (m_vboId != 0)
		{
			glDeleteBuffers(1, &m_vboId);
			m_vboId = 0;
		}
	}

	bool VertexBuffer::bind() const
	{
		if (m_vboId != 0)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
			return true;
		}
		else
		{
			return false;
		}

	}

	void VertexBuffer::unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}