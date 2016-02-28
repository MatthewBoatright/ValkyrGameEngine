#pragma once

#include "irenderable.h"

namespace Valkyr { namespace Graphics { 

	class IRenderer
	{
	public:
		virtual void begin() {}
		virtual void end() {}
		virtual void submit(const IRenderable * renderable) = 0;
		virtual void flush() = 0;

	};

} }