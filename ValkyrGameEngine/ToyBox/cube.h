#pragma once

#include "../Buffers/vertex_array.h"

namespace Valkyr { namespace Graphics { 

	class Cube
	{
	public:
		GLuint m_Triangles;
		GLuint m_ComponentCount;

		Cube(float width, float height, float depth);

	protected:
	private:
		VertexArray * m_VertexArray;
		inline const VertexArray* getVAO() const { return m_VertexArray; }

	};

} }

