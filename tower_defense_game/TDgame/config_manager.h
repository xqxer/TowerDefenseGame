//config_manager.h
#ifndef _CONFIG_MANAGER_H_
#define _CONFIG_MANAGER_H_

#include "manager.h"
#include "map.h"
#include "wave.h"

#include <SDL.h>
#include <cJSON.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class ConfigManager : public Manager<ConfigManager>
{
	friend class Manager<ConfigManager>;

public:

	//主页面数据
	struct BasicTemplete
	{
		std::string window_title = u8"哈基米塔防";
		int window_width = 1280;
		int window_height = 720;
	};

	//玩家方数据
	struct PlayerTemplete
	{
		double speed = 3;
		double normal_attact_interval = 0.5;
		double normal_attact_damage = 0;
		double skill_interval = 10;
		double skill_damage = 1;
	};

	//防御塔数据
	struct TowerTemplate
	{
		double interval[10] = { 1 };		//攻击间隔
		double damage[10] = { 25 };			//攻击伤害
		double view_range[10] = { 5 };		//视野范围
		double cost[10] = { 50 };			//建造花费
		double upgrade_cost[9] = { 75 };	//升级花费
	};

	//敌人数据
	struct EnemyTemplate
	{
		double hp = 100;				//血量
		double speed = 1;				//速度
		double damage = 1;				//伤害
		double reward_ratio = 0.5;		//回报率[金币掉落概率]
		double recover_interval = 10;	//恢复速率
		double recover_range = 0;		//恢复范围[0:自身回复]
		double recover_intensity = 25;	//恢复强度
	};

public:
	Map map;
	std::vector<Wave> wave_list;

	int level_archer = 0;
	int level_axeman = 0;
	int level_gunner = 0;

	bool is_game_win = true;
	bool is_game_over = false;
	SDL_Rect rect_tile_map = { 0 };

	BasicTemplete basic_templete;

	PlayerTemplete player_template;

	TowerTemplate archer_temlate;
	TowerTemplate axeman_temlate;
	TowerTemplate gunner_temlate;

	EnemyTemplate slim_template;
	EnemyTemplate king_slim_template;
	EnemyTemplate skeleton_template;
	EnemyTemplate goblin_template;
	EnemyTemplate goblin_priest_template;

	const double num_initial_hp = 10;
	const double num_initial_coin = 100;
	const double num_coins_per_prop = 10;

public:
	bool load_level_config(const std::string& path)
	{

	}
	bool load_game_config(const std::string& path)
	{

	}

protected:
	ConfigManager() = default;
	~ConfigManager() = default;

private:

};


#endif //!_CONFIG_MANAGER_H_
