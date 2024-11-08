//tile.h
#ifndef _TILE_H_
#define _TILE_H_

#include <vector>

const int TileSize = 48;

// ��Ƭ
struct Tile
{
	//ö����Ƭ����
	enum class Direction
	{
		None = 0,
		Up,
		Down,
		Left,
		Right
	};

	int terrian = 0;								//����
	int	decoration = -1;							//װ��
	int SpecialFlag = -1;							//�����־
	bool HasTower = false;							//�ж����޷�����
	Direction direction = Direction::None;			//��Ƭ����
};

typedef std::vector<std::vector<Tile>> TileMap;		//��Ϸ��ͼ

#endif //!_TILE_H_
