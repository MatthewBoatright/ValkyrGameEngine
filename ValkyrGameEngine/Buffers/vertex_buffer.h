#pragma once

#include <vector>

#include <GL/glew.h>

#include <glm/glm.hpp>

#include "../Common/vertex.h"

namespace Valkyr { namespace Graphics { 

	class VertexBuffer
	{
	public:
		VertexBuffer(GLfloat * data, GLsizei count, GLuint bufferSize);
		VertexBuffer(const std::vector<glm::vec2> vertices);
		VertexBuffer(const std::vector<glm::vec3> vertices);
		VertexBuffer(const std::vector<glm::vec4> vertices);
		VertexBuffer(const std::vector<Vertex> vertices);
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