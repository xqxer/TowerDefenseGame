//tile.h
#ifndef _MAP_H_
#define _MAP_H_

#include "tile.h"
#include "route.h"

#include <SDL.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

class Map
{
public:
	typedef std::unordered_map<int, Route> SpawnerRoutePool;	//路径生成器

public:
	Map() = default;
	~Map() = default;

	bool load(const std::string& path) {
		std::ifstream file(path);
		// 打开失败
		if (!file.good()) return false;
		
		// 打开成功
		TileMap tile_map_tmp;

		int idx_x = -1, idx_y = -1;

		std::string str_line;
		while (std::getline(file, str_line))
		{
			str_line = trim_str(str_line);
			if (str_line.empty())	continue;
			idx_x = -1, idx_y++;
			tile_map_tmp.emplace_back();

			std::string str_tile;
			std::stringstream str_stream(str_line);
			while (std::getline(str_stream, str_tile, ','))
			{
				idx_x++;
				tile_map_tmp[idx_y].emplace_back();
				Tile& tile = tile_map_tmp[idx_y].back();
				load_tile_from_string(tile, str_tile);
			}
		}
		file.close();

		if (tile_map_tmp.empty() || tile_map_tmp[0].empty()) return false;
		
		tile_map = tile_map_tmp;
		


		generate_map_cache();



		return true;
	}

	size_t get_width() const
	{
		if (tile_map.empty())	return 0;

		return tile_map[0].size();
	}

	size_t get_height() const
	{
		return tile_map.size();
	}

	const TileMap& get_tile_map() const
	{
		return tile_map;
	}

	const SDL_Point& get_idx_home() const
	{
		return idx_home;
	}

	const SpawnerRoutePool& get_idx_spawner_pool() const
	{
		return spawner_route_pool;
	}

	void place_tower(const SDL_Point& idx_tile)
	{
		tile_map[idx_tile.y][idx_tile.x].HasTower = true;
	}

private:
	TileMap tile_map;
	SDL_Point idx_home = { 0 };		//索引位置
	SpawnerRoutePool spawner_route_pool;

private:
	// 截取首尾空白字符
	std::string trim_str(const std::string& str)
	{
		size_t begin_idx = str.find_first_not_of(" \t");
		if (begin_idx == std::string::npos)	return "";
		size_t end_idx = str.find_last_not_of(" \t");
		size_t idx_range = end_idx - begin_idx + 1;

		return str.substr(begin_idx, idx_range);
	}

	void load_tile_from_string(Tile& tile, const std::string& str)
	{
		std::string str_tidy = trim_str(str);

		std::string str_value;
		std::vector<int> values;
		std::stringstream str_stream(str_tidy);

		while (std::getline(str_stream, str_value, '\\'))
		{
			int value;
			try
			{
				value = std::stoi(str_value);
			}
			catch (const std::invalid_argument&)
			{
				value = -1;
			}
			values.push_back(value);
		}
		tile.terrian = (values.size() < 1 || values[0] < 0) ? 0 : values[0];
		tile.decoration = (values.size() < 2) ? -1 : values[1];
		tile.direction = (Tile::Direction)((values.size() < 3 || values[2] < 0) ? 0 : values[2]);
		tile.SpecialFlag = (values.size() <= 3) ? -1 : values[3];
	}

	//地图缓存生成
	void generate_map_cache()
	{
		//【遍历地图所有单元格】
		for (int y = 0; y < get_height(); y++) {
			for (int x = 0; x < get_width(); x++) {
				const Tile& tile = tile_map[x][y];
				
				if (tile.SpecialFlag < 0) continue;

				if (tile.SpecialFlag == 0)
				{
					idx_home.x = x;
					idx_home.y = y;
				}
				else
				{
					spawner_route_pool[tile.SpecialFlag] = Route(tile_map, { x,y });
				}
			}
		}
	}
};


#endif //!_MAP_H_
