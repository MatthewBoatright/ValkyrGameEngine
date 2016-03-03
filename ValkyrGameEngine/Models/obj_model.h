#pragma once

#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>

#include <GL/glew.h>

#include <glm/glm.hpp>

#include "../Common/objloader.hpp"
#include "../Common/vboindexer.hpp"

#include "../Buffers/vertex_array.h"
#include "../Buffers/vertex_buffer.h"
#include "../Buffers/index_buffer.h"

#include "../Renderers/irenderable.h"

namespace Valkyr { namespace Graphics { 

	// TODO: Make base class and other classes to support other model formats.
	class OBJModel : public IRenderable
	{
	public:
		OBJModel(const char * filename);

		void bind();
		void unbind();

	private:
		bool init(const char * filename);
		void loadDefaultModel();
	};

} }