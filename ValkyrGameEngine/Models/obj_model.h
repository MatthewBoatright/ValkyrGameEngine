#pragma once

#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>

#include <GL/glew.h>

#include <glm/glm.hpp>

#include "../Buffers/vertex_array.h"
#include "../Buffers/vertex_buffer.h"
#include "../Buffers/index_buffer.h"

namespace Valkyr { namespace Graphics { 

	// TODO: Make base class and other classes to support other model formats.
	class OBJModel
	{
	public:
		VertexArray m_VertexArray;
		unsigned int m_Size;
		//IndexBuffer m_IndexBuffer;

		OBJModel(const char * filename);

	private:
		bool init(const char * filename);
		void loadDefaultModel();

		inline bool fileExists(const std::string name)
		{
			struct stat buffer;
			return (stat(name.c_str(), &buffer) == 0);
		}

		bool m_HasNormals = false;
		bool m_HasUV = false;
	};

} }