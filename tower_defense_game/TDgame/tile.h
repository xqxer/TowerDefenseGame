//tile.h
#ifndef _TILE_H_
#define _TILE_H_

#include <vector>

const int TileSize = 48;

// 瓦片
struct Tile
{
	//枚举瓦片方向
	enum class Direction
	{
		None = 0,
		Up,
		Down,
		Left,
		Right
	};

	int terrian = 0;								//地形
	int	decoration = -1;							//装饰
	int SpecialFlag = -1;							//特殊标志
	bool HasTower = false;							//判断有无防御塔
	Direction direction = Direction::None;			//瓦片方向
};

typedef std::vector<std::vector<Tile>> TileMap;		//游戏地图

#endif //!_TILE_H_
