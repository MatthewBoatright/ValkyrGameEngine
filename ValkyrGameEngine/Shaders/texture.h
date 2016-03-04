#pragma once

#include <string>

#include <GL/glew.h>

#include <FreeImage.h>

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

namespace Valkyr { namespace Graphics { 

	class Texture
	{
	public:
		Texture(const char * texturePath, GLenum target = GL_TEXTURE_2D);

		bool load();
		void bind(GLenum textureUnit);
		void unbind();

	private:
		std::string m_TextureFile;
		GLenum m_TextureTarget;
		GLuint m_TextureID;

		bool loadDDS();

	};

} }