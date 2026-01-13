#pragma once

namespace OpenGLLens
{
	class VertexBuffer
	{
	public:
		VertexBuffer(void* data,size_t size);	
		~VertexBuffer();

		bool bind() const;
		void unbind() const;
	private:
		unsigned int m_vboId;
	};
}


