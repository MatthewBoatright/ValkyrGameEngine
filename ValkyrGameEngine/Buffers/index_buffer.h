#pragma once

#include <GL/glew.h>

namespace Valkyr { namespace Graphics {

	class IndexBuffer
	{
	public:
		IndexBuffer(GLuint * data, GLsizei count);
		~IndexBuffer();

		void bind() const;
		void unbind() const;

	protected:
	private:
		GLuint m_IndexBufferID;

	};

} }