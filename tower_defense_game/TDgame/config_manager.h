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

	//��ҳ������
	struct BasicTemplete
	{
		std::string window_title = u8"����������";
		int window_width = 1280;
		int window_height = 720;
	};

	//��ҷ�����
	struct PlayerTemplete
	{
		double speed = 3;
		double normal_attact_interval = 0.5;
		double normal_attact_damage = 0;
		double skill_interval = 10;
		double skill_damage = 1;
	};

	//����������
	struct TowerTemplate
	{
		double interval[10] = { 1 };		//�������
		double damage[10] = { 25 };			//�����˺�
		double view_range[10] = { 5 };		//��Ұ��Χ
		double cost[10] = { 50 };			//���컨��
		double upgrade_cost[9] = { 75 };	//��������
	};

	//��������
	struct EnemyTemplate
	{
		double hp = 100;				//Ѫ��
		double speed = 1;				//�ٶ�
		double damage = 1;				//�˺�
		double reward_ratio = 0.5;		//�ر���[��ҵ������]
		double recover_interval = 10;	//�ָ�����
		double recover_range = 0;		//�ָ���Χ[0:����ظ�]
		double recover_intensity = 25;	//�ָ�ǿ��
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
