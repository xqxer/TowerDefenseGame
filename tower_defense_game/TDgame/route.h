//route.h
#ifndef _ROUTE_H_
#define _ROUTE_H_

#include "tile.h"
#include <SDL.h>

class Route
{
public:
    typedef std::vector<SDL_Point>  IdxList;

public:
	Route() = default;

	Route(const TileMap& map,const SDL_Point& idx_origin)
	{
		size_t width_map = map[0].size();
		size_t height_map = map.size();

		SDL_Point idx_next = idx_origin;

        while (true)
        {
            // error��Խ���ж�
            if (idx_next.x >= width_map || idx_next.y >= height_map)
                break;
            // error��Խ���ж�over

            if (check_duplicate_idx(idx_next))
                break;
            else
                idx_list.push_back(idx_next);

            bool is_next_dir_exist = true;
            const Tile& tile = map[idx_next.y][idx_next.x];

            //�ִ�Ŀ���
            if (tile.SpecialFlag == 0)
                break;

            switch (tile.direction)
            {
            case Tile::Direction::Up:
                idx_next.y--;
                break;
            case Tile::Direction::Down:
                idx_next.y++;
                break;
            case Tile::Direction::Left:
                idx_next.x--;
                break;
            case Tile::Direction::Right:
                idx_next.x++;
                break;

                // error���޷���
            default:
                is_next_dir_exist = false;
                break;
                // error���޷���over
            }

                // error����·��
            if (!is_next_dir_exist)
                break;
                // error����·��over
        }
	}

    ~Route() = default;

    const IdxList& get_idx_list() const {
        return idx_list;
    }


private:
    IdxList idx_list;
private:
    bool check_duplicate_idx(const SDL_Point& target_idx) {
        for (const SDL_Point& idx : idx_list) {
            if (idx.x == target_idx.x && idx.y == target_idx.y)
                return true;
        }
        return false;
    }

};



#endif //!_ROUTE_H_