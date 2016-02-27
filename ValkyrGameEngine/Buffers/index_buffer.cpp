#include "index_buffer.h"

namespace Valkyr { namespace Graphics { 
	
	IndexBuffer::IndexBuffer(GLuint * data, GLsizei count)
	{
		glGenBuffers(1, &m_IndexBufferID);
		bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
		unbind();
	}
	
	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_IndexBufferID);
	}

	void IndexBuffer::bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
	}

	void IndexBuffer::unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}
}

