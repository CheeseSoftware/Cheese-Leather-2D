#pragma once

#include "types.h"

class World;

/* Other names:
 * BlockData
 * ComplexBlock
 * "TileEntity"
 * BlockEntioty
*/
class IBlockEntity {
public:
	virtual ~IBlockComponent() {}

	virtual void onPlace(World *world, u32vec2 position) = 0;
	virtual void onDestroy(World *world, u32vec2 position) = 0;

	//virtual void onVolumeChange(World *world, u32vec2 position, u32 volume) = 0;

	//void onPlayerClick(World *world, u32vec2 position, MouseEventType mouseEventType, int mouseButton) = 0;
};

class BlockChest : virtual public IBlockEntity {
public:
	virtual ~IBlockComponent() {}
};