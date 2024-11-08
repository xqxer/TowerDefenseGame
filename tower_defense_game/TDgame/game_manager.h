//game_manager.h
#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include "manager.h"

#include <cJSON.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL2_gfxPrimitives.h>
class GameManager : public Manager<GameManager>
{
	friend class Manager<GameManager>;
public:
	int run(int argc, char** argv) {

		Uint64 last_counter = SDL_GetPerformanceCounter();
		const Uint64 counter_freq = SDL_GetPerformanceFrequency();

		while (!IsQuit)
		{
			while(SDL_PollEvent(&event))
			{
				on_input();
			}

			Uint64 current_counter = SDL_GetPerformanceCounter();
			double delta = (double)(current_counter - last_counter) / counter_freq;
			last_counter = current_counter;

			if (delta * 1000 < 1000.0 / fps)
			{
				SDL_Delay(1000.0 / fps - delta * 1000);
			}

			on_update(delta);

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);

			on_render();

			SDL_RenderPresent(renderer);
		}
		return 0;
	}

protected:
	GameManager()
	{
		InitAssert(!SDL_Init(SDL_INIT_EVERYTHING), u8"SDL2 ��ʼ��ʧ�ܣ�");
		InitAssert(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG),u8"SDL_image ��ʼ��ʧ�ܣ�");
		InitAssert(Mix_Init(MIX_INIT_MP3),u8"SDL_mixer ��ʼ��ʧ�ܣ�");
		InitAssert(!TTF_Init(), u8"SDL_ttf ��ʼ��ʧ�ܣ�");

		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

		SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");//	��ʾ ME "���뷨"

		window = SDL_CreateWindow(u8"����������",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			1280, 720, SDL_WINDOW_SHOWN);
		InitAssert(window, u8"��Ϸ���ڴ���ʧ�ܣ�");

		//
		renderer = SDL_CreateRenderer(window, -1,
			SDL_RENDERER_ACCELERATED	|
			SDL_RENDERER_PRESENTVSYNC	| 
			SDL_RENDERER_TARGETTEXTURE	);
		InitAssert(renderer, u8"��Ⱦ������ʧ�ܣ�");
	}
	~GameManager()
	{
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);

		TTF_Quit();
		Mix_Quit();
		IMG_Quit();
		SDL_Quit();
	}
private:
	SDL_Event event;
	bool IsQuit = false;

	const int fps = 60;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

private:
	void InitAssert(bool flag,const char* err_msg)
	{
		if (flag) return;

		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, u8"��Ϸ����ʧ��", err_msg, window);
		exit(-1);
	}

	//�¼�����
	void on_input()
	{

	}
	//��������
	void on_update(double delta = 1000)
	{

	}
	//���ƻ���
	void on_render()
	{

	}
};




#endif // _GAME_MANAGER_H_
