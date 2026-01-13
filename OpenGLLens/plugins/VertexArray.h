#pragma once
namespace OpenGLLens
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		bool bind() const;
		void unbind() const;

		void addBuffer(const class VertexBuffer& vb, const class VertexBufferLayout& layout);
	private:
		unsigned int m_vaoId;
	};
}


