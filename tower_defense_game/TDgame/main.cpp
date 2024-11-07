//main.c
#define SDL_MAIN_HANDLED

#include "manager.h"
#include "GameManager.h"
#include <iostream>



int main(int argc, char** argv) {
	//GameManager* instance = GameManager::instance();
	//instance->run(argc, argv);
	//return 0;
	return GameManager::instance()->run(argc, argv);
}