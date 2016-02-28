#pragma once

#include <vector>
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include "base_renderable.h"

namespace Valkyr { namespace Graphics { 

	class BaseRenderer
	{
	public:
		virtual void begin() {}
		virtual void end() {}
		virtual void submit(const BaseRenderable * renderable) = 0;
		virtual void flush() = 0;

	protected:
	private:
	};

} }