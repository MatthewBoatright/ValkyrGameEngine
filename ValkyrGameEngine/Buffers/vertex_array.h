#pragma once

#include <GL/glew.h>
#include <vector>
#include "vertex_buffer.h"

namespace Valkyr { namespace Graphics { 
	
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void bind() const;
		void unbind() const;
		void addBuffer(VertexBuffer * buffer, GLuint index);

	protected:
	private:
		GLuint m_VertexArrayID;
		std::vector<VertexBuffer*> m_Buffers;

	};

} }