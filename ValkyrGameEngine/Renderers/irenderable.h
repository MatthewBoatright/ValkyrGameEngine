#pragma once

#include "../Buffers/index_buffer.h"
#include "../Buffers/vertex_buffer.h"
#include "../Buffers/vertex_array.h"
#include "../Shaders/shader.h"

namespace Valkyr { namespace Graphics { 

	class IRenderable
	{
	public:
		inline const VertexArray * getVertexArray() const { return m_VertexArray; }
		inline const IndexBuffer * getIndexBuffer() const { return m_IndexBuffer; }
		IRenderable() {}

	protected:
		VertexArray * m_VertexArray;
		IndexBuffer * m_IndexBuffer;


	};

} }