#pragma once

#include "../Buffers/vertex_array.h"
#include "../Buffers/vertex_buffer.h"
#include "../Buffers/index_buffer.h"
#include <glm/vec3.hpp> 
#include <glm/vec4.hpp> 
#include <glm/mat4x4.hpp> 
#include "../Utilities/bmp_loader.h"

namespace Valkyr { namespace Graphics { 

	class Cube
	{
	public:
		GLuint m_Triangles;
		GLuint m_ComponentCount;

		Cube(float width, float height, float depth);
		Cube(glm::vec3 dimensions, glm::vec3 position, glm::vec4 color);

	protected:
	private:
		VertexArray * m_VertexArray;
		IndexBuffer * m_IndexBuffer;
		inline const VertexArray* getVAO() const { return m_VertexArray; }

	};

} }

