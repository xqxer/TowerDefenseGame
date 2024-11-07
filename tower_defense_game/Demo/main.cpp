#define SDL_MAIN_HANDLED

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <cJSON.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL2_gfxPrimitives.h>

void test_json() 
{
	std::ifstream file("item/test.json");
	if (!file.good()) 
	{
		std::cout << "�޷����ļ�\n";
		return;
	}
	std::stringstream str_stream;
	str_stream << file.rdbuf();
	file.close();

	cJSON* json_root = cJSON_Parse(str_stream.str().c_str());

	cJSON* json_name = cJSON_GetObjectItem(json_root, "name");
	cJSON* json_age = cJSON_GetObjectItem(json_root, "age");
	cJSON* json_pets = cJSON_GetObjectItem(json_root, "pets");

	std::cout << json_name->string << ":" << json_name->valuestring << "\n";
	std::cout << json_age->string << ":" << json_age->valueint << "\n";
	cJSON* json_item = nullptr;
	cJSON_ArrayForEach(json_item, json_pets) {
		std::cout << json_item->valuestring << "\n";
	}

}
void test_csv()
{
	std::ifstream file("item/test.csv");
	if (!file.good())
	{
		std::cout << "�޷����ļ�" << std::endl;
		return;
	}

	std::string str_line;
	while (std::getline(file, str_line))
	{
		std::string str_grid;
		std::istringstream str_stream(str_line);
		while (std::getline(str_stream, str_grid, ','))
		{
			std::cout << str_grid << " ";
		}
		std::cout << std::endl;
	}

	file.close();
}

int main() {

	// // //��ʼ��
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	Mix_Init(MIX_INIT_MP3);
	TTF_Init();
	// // //��ʼ��


	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	SDL_Window* window = SDL_CreateWindow(u8"�������", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_Surface* suf_img = IMG_Load("item/avatar.jpg");
	SDL_Texture* tex_img = SDL_CreateTextureFromSurface(renderer, suf_img);

	TTF_Font* font = TTF_OpenFont("item/ipix.ttf", 32);
	SDL_Color color = { 255,255,255,255 };//white
	SDL_Surface* suf_text = TTF_RenderUTF8_Blended(font, u8"˵�ĵ���", color);
	SDL_Texture* tex_text = SDL_CreateTextureFromSurface(renderer, suf_text);

	Mix_Music* music = Mix_LoadMUS("item/music.mp3");
	Mix_FadeInMusic(music, -1, 1500);

	int fps = 60;
	bool IsQuit = false;

	SDL_Event event;
	SDL_Point pos_cursor = { 0,0 };
	SDL_Rect rect_img,rect_text;
	// �߾��ȼ�ʱ��
	Uint64 last_counter = SDL_GetPerformanceCounter();
	Uint64 conter_freq = SDL_GetPerformanceFrequency();

	rect_img.w = suf_img->w;
	rect_img.h = suf_img->h;

	rect_text.w = suf_text->w;
	rect_text.h = suf_text->h;

	while (!IsQuit)
	{
		while (SDL_PollEvent(&event))
		{
			//�����¼�
			if (event.type == SDL_QUIT)
			{
				IsQuit = true;
			}
			else if (event.type == SDL_MOUSEMOTION)
			{
				pos_cursor.x = event.motion.x;
				pos_cursor.y = event.motion.y;
			}
		}

		Uint64 current_counter = SDL_GetPerformanceCounter();
		double delta = (double)(current_counter - last_counter) / conter_freq;
		last_counter = current_counter;

		if (delta * 1000 < 1000.0 / fps)
		{
			SDL_Delay(1000.0 / fps - delta * 1000);
		}

		//��������
		rect_img.x = pos_cursor.x;
		rect_img.y = pos_cursor.y;

		rect_text.x = pos_cursor.x;
		rect_text.y = pos_cursor.y;

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		//��Ⱦ��ͼ
		SDL_RenderCopy(renderer, tex_img, nullptr, &rect_img);
		filledCircleRGBA(renderer, pos_cursor.x, pos_cursor.y, 50, 255, 0, 0, 125);
		SDL_RenderCopy(renderer, tex_text, nullptr, &rect_text);

		SDL_RenderPresent(renderer);
	}


}