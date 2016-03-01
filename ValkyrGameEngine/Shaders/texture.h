#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <FreeImage.h>

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

namespace Valkyr { namespace Graphics { 

	class Texture
	{
	public:
		Texture(const char * texturePath);

		void bind();
		void unbind();

	private:
		GLuint m_TextureID;

		bool init(const char * texturePath);
		bool loadDDS(const char * texturePath);

	};

} }