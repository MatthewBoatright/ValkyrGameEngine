#pragma once

#include <GL/glew.h>

namespace Valkyr { namespace Graphics { 

	class VertexBuffer
	{
	public:
		VertexBuffer(GLfloat* data, GLsizei count, GLuint componentCount);
		~VertexBuffer();

		void bind() const;
		void unbind() const;
		inline GLuint getComponentCount() const { return m_ComponentCount; }

	protected:
	private:
		GLuint m_VertexBufferID;
		GLuint m_ComponentCount;

	};

} }