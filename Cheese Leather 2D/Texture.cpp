#include "Texture.h"

#include <iostream>
#include <SOIL.h>

Texture::Texture(std::string path)
{
	int width = 0, height = 0;
	//std::cout << "\"" << std::string("textures/" + path).c_str() << "\"";
	GLuint image = SOIL_load_OGL_texture
		(std::string("textures/" + path).c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	if (image)
	{
		m_glTexture = image;
		m_width = width;
		m_height = height;
		m_path = path;
	}
	else
		std::cout << "Unable to load texture \"" << path << "\": " << SOIL_last_result() << std::endl;
}

GLuint Texture::getGlTexture()
{
	return m_glTexture;
}

int Texture::getWidth()
{
	return m_width;
}

int Texture::getHeight()
{
	return m_height;
}

std::string Texture::getPath()
{
	return m_path;
}

std::string Texture::getFileName()
{
	//TODO: Return file name (texture.png instead of karl/bertil/texture.png)
	return "";
}