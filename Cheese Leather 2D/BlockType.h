#pragma once

#include <string>

#include "types.h"
#include "DefaultBlock.h"

class BlockEntity;

struct BlockType {
	std::string name;
	u32 id;

	DefaultBlock defaultBlockType = DefaultBlock::NONE;

	//TextureAtlas::SubTexture blockTexture


	std::string texture;

	BlockEntity *blockEntity = nullptr;

	bool isBlockEntity() {
		return blockEntity != nullptr;
	}


};