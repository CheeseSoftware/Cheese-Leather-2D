#include "BlockRegister.h"

#include "BlockType.h"


BlockRegister::BlockRegister() {

}

BlockRegister::~BlockRegister() {

}


u16 BlockRegister::registerBlock(BlockType *blockType) {
	u16 id = m_blocks.size();

	m_blocks.push_back(blockType);
	m_blockMap.emplace(blockType->name, blockType);

	if (blockType->defaultBlockType != DefaultBlock::NONE) {
		m_defaultBlocks.emplace(blockType->defaultBlockType, blockType);
	}
	
	// TODO: finish registerBlock

	return id;
}


BlockType *BlockRegister::getBlock(u16 id) {
	if (id < m_blocks.size())
		return m_blocks[id];
	else
		return nullptr;
}

BlockType *BlockRegister::getBlock(std::string name) {
	auto it = m_blockMap.find(name);
	if (it != m_blockMap.end())
		return it->second;
	else
		return nullptr;
}

BlockType *BlockRegister::getBlock(DefaultBlock defaultBlockType) {
	auto it = m_defaultBlocks.find(defaultBlockType);
	if (it != m_defaultBlocks.end())
		return it->second;
	else
		return nullptr;
}
