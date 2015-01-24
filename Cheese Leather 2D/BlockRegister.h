#pragma once

#include <string>
#include <vector>
#include <unordered_map> 
#include <string>


#include "types.h"

struct BlockDefinition;
class BlockEntity;

struct BlockType;
enum class DefaultBlock;

class BlockRegister {
public:
	BlockRegister();
	~BlockRegister();

	u16 registerBlock(BlockType *blockType);

	BlockType *getBlock(u16 id);
	BlockType *getBlock(std::string name);
	BlockType *getBlock(DefaultBlock defaultBlockType);

	// BlockType *getGameBlock<Enum>(Enum enum);

	// TextureAtlas *getTextureAtlas();
private:
	std::vector<BlockType*> m_blocks;
	std::unordered_map<std::string, BlockType*> m_blockMap;
	std::unordered_map<DefaultBlock, BlockType*> m_defaultBlocks;
	std::unordered_map<std::string, u16> m_textures;

	// TextureAtlas *m_textureAtlas;
};

