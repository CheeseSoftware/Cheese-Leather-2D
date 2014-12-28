#pragma once

#include <string>
#include <GL\glew.h>

class Texture {
public:
	Texture(const Texture &other) = delete; 
	Texture operator=(const Texture &other) = delete;
	Texture(Texture &&other) { auto temp = m_glTexture; m_glTexture = other.m_glTexture; other.m_glTexture = temp; }

	Texture(std::string path);

	GLuint getGlTexture();
	int getWidth();
	int getHeight();
	std::string getPath();
	std::string getFileName();
private:
	GLuint m_glTexture;
	std::string m_path;
	int m_width;
	int m_height;
};