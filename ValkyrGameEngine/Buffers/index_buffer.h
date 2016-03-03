#pragma once

#include <GL/glew.h>

#include <vector>

#include <glm/glm.hpp>

namespace Valkyr { namespace Graphics {

	class IndexBuffer
	{
	public:
		IndexBuffer(GLuint * data, GLsizei count);
		IndexBuffer(const std::vector<unsigned short> indices);
		~IndexBuffer();

		void bind() const;
		void unbind() const;
		inline const GLsizei getSize() const { return m_Size; }

	protected:
	private:
		GLuint m_IndexBufferID;
		GLsizei m_Size;

	};

} }