#pragma once

#include <string>
#include <gl\glew.h>

class Texture {
public:
	Texture(const Texture &other) = delete; 
	Texture operator=(const Texture &other) = delete;
	Texture(Texture &&other) { auto temp = m_glTexture; m_glTexture = other.m_glTexture; other.m_glTexture = temp; }

	Texture(std::string path);

	GLuint getGlTexture();
private:
	GLuint m_glTexture;
};