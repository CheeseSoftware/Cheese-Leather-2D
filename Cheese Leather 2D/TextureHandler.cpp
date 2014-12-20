#include "TextureHandler.h"

#include <iostream>

#include "Texture.h"

TextureHandler::TextureHandler()
{
	m_textureIdMap = std::unordered_map<std::string, size_t>();
	m_textureList = std::vector<Texture*>();

	loadTexture("carl-bildt.jpg");
}

TextureHandler::~TextureHandler()
{

}


size_t TextureHandler::getTextureId(std::string textureName)
{
	auto it = m_textureIdMap.find(textureName);
	if (it != m_textureIdMap.end())
	{
		return it->second;
	}
	return -1;
}

Texture *TextureHandler::getTexture(size_t id)
{
	if (id >= 0 && id < m_textureList.size())
	{
		Texture *texture = m_textureList.at(id);
		return texture;
	}
	return nullptr;
}

Texture *TextureHandler::getTexture(std::string textureName)
{
	size_t id = getTextureId(textureName);
	if (id != -1)
	{
		Texture *texture = getTexture(id);
		if (texture != nullptr)
			return texture;
		else
			printf("ERROR: Some idiot added a null texture to TextureHandler.");
	}
	return nullptr;
}

/******************************************
*              Private                    *
*******************************************/

void TextureHandler::loadTexture(std::string path)
{
	Texture *texture = new Texture(path);
	if (texture)
	{
		m_textureList.push_back(texture);
		size_t id = m_textureList.size() - 1;
		m_textureIdMap.emplace(path, id);
		std::cout << "Successfully loaded texture \"" << path << "\"" << std::endl;
	}
}

void TextureHandler::unloadTexture(std::string name)
{
	size_t id = getTextureId(name);
	if (id != -1)
	{
		m_textureIdMap.erase(name);
		m_textureList.erase(m_textureList.begin() + id);
	}
}