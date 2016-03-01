#pragma once

#include <vector>

#include <GL/glew.h>

#include <glm/glm.hpp>

namespace Valkyr { namespace Graphics { 

	class VertexBuffer
	{
	public:
		VertexBuffer(GLfloat * data, GLsizei count, GLuint bufferSize);
		VertexBuffer(const std::vector<glm::vec2> indexed_vertices);
		VertexBuffer(const std::vector<glm::vec3> indexed_vertices);
		VertexBuffer(const std::vector<glm::vec4> indexed_vertices);
		~VertexBuffer();

		void bind() const;
		void unbind() const;
		inline GLuint getBufferSize() const { return m_BufferSize; }

	protected:
	private:
		GLuint m_VertexBufferID;
		GLuint m_BufferSize;

	};

} }