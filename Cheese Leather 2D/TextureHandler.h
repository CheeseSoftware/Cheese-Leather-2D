#pragma once

#include <unordered_map>
#include <string>

class Texture;

class TextureHandler {

	//path a: game/textures/steve/huvud.png
	//path b: random/äggmod/textures/steve/huvud.png
	//name a: steve/huvud.png
	//name b: steve/huvud.png
	// b will change texture of a.

public:
	TextureHandler();
	~TextureHandler();
	size_t getTextureId(std::string textureName);
	Texture *getTexture(size_t id);
	Texture *getTexture(std::string textureName);
	Texture *getBlockTexture(int blockId);

	void loadTexture(std::string path);
	void unloadTexture(std::string name);
private:
	std::unordered_map<std::string, size_t> m_textureIdMap;
	std::vector<Texture*> m_textureList;
};