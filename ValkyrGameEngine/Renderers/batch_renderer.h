#pragma once

#include "irenderer.h"

namespace Valkyr { namespace Graphics { 

	class BatchRenderer : public IRenderer
	{
	public:
		BatchRenderer();
		~BatchRenderer();

		void begin() override;
		void end() override;
		void submit(const IRenderable * renderable) override;
		void flush() override;

	private:
		GLuint m_VAO;
		GLuint m_VBO;

	};

} }