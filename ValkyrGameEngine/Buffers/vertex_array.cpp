#include "vertex_array.h"

namespace Valkyr { namespace Graphics { 

	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_VertexArrayID);
	}

	VertexArray::~VertexArray()
	{
		for (int i = 0; i < m_Buffers.size(); i++)
			delete m_Buffers[i];

		glDeleteVertexArrays(1, &m_VertexArrayID);
	}

	void VertexArray::bind() const
	{
		glBindVertexArray(m_VertexArrayID);
	}

	void VertexArray::unbind() const
	{
		glBindVertexArray(0);
	}

	void VertexArray::addBuffer(VertexBuffer * buffer, GLuint index)
	{
		bind();
		buffer->bind();
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, (void*)0);
		buffer->unbind();
		unbind();
	}

} }