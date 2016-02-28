#pragma once

#include "base_renderer.h"
#include "../Buffers/index_buffer.h"

namespace Valkyr { namespace Graphics { 

	class BatchRenderer : public BaseRenderer
	{
	public:
		BatchRenderer();
		~BatchRenderer();

		void begin() override;
		void end() override;
		void submit(const BaseRenderable * renderable) override;

	protected:
	private:
		GLuint m_VAO;
		GLuint m_VBO;
		IndexBuffer * m_IndexBuffer;
		GLsizei m_IndexCount;

		void init();

	};

} }