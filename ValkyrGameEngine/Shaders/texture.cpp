#include "texture.h"

namespace Valkyr { namespace Graphics { 

	Texture::Texture(const char * texturePath, GLenum target)
		: m_TextureFile(m_TextureFile), m_TextureTarget(target)
	{}

	void Texture::bind(GLenum textureUnit)
	{
		glActiveTexture(textureUnit);
		glBindTexture(m_TextureTarget, m_TextureID);
	}

	void Texture::unbind()
	{
		glDisable(m_TextureID);
	}

	bool Texture::load()
	{
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		FIBITMAP *dib(0);
		BYTE* bits(0);
		unsigned int width(0), height(0);

		fif = FreeImage_GetFileType(m_TextureFile.c_str(), 0);
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(m_TextureFile.c_str());
		if (fif == FIF_DDS)
			return loadDDS();
		if (fif == FIF_UNKNOWN)
			return false;

		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, m_TextureFile.c_str());
		if (!dib)
			return false;

		bits = FreeImage_GetBits(dib);
		width = FreeImage_GetWidth(dib);
		height = FreeImage_GetHeight(dib);
		if ((bits == 0) || (width == 0) || (height == 0))
			return false;

		glGenTextures(1, &m_TextureID);
		glBindTexture(m_TextureTarget, m_TextureID);
		glTexImage2D(m_TextureTarget, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, (void*)bits);
		glTexParameteri(m_TextureTarget, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(m_TextureTarget, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(m_TextureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(m_TextureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		return true;
	}

	bool Texture::loadDDS()
	{
		unsigned char header[124];
		FILE *fp;

		fp = fopen(m_TextureFile.c_str(), "rb");
		if (fp == NULL) 
		{
			printf("%s could not be opened.\n", m_TextureFile.c_str());
			return false;
		}

		char filecode[4];
		fread(filecode, 1, 4, fp);
		if (strncmp(filecode, "DDS ", 4) != 0) 
		{
			fclose(fp);
			return false;
		}

		fread(&header, 124, 1, fp);

		unsigned int height = *(unsigned int*)&(header[8]);
		unsigned int width = *(unsigned int*)&(header[12]);
		unsigned int linearSize = *(unsigned int*)&(header[16]);
		unsigned int mipMapCount = *(unsigned int*)&(header[24]);
		unsigned int fourCC = *(unsigned int*)&(header[80]);


		unsigned char * buffer;
		unsigned int bufsize;
		bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
		buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
		fread(buffer, 1, bufsize, fp);
		fclose(fp);

		unsigned int components = (fourCC == FOURCC_DXT1) ? 3 : 4;
		unsigned int format;
		switch (fourCC)
		{
		case FOURCC_DXT1:
			format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
			break;
		case FOURCC_DXT3:
			format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
			break;
		case FOURCC_DXT5:
			format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
			break;
		default:
			free(buffer);
			return false;
		}

		glGenTextures(1, &m_TextureID);

		glBindTexture(m_TextureTarget, m_TextureID);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
		unsigned int offset = 0;

		for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
		{
			unsigned int size = ((width + 3) / 4)*((height + 3) / 4)*blockSize;
			glCompressedTexImage2D(m_TextureTarget, level, format, width, height, 0, size, buffer + offset);

			offset += size;
			width /= 2;
			height /= 2;

			if (width < 1) width = 1;
			if (height < 1) height = 1;
		}

		free(buffer);

		return true;
	}

} }