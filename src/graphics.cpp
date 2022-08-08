#include "graphics.h"
#include "rom.h"
#include <SDL.h>
#include <iostream>
#include <string>

static SDL_Window*	 window;
static SDL_Renderer* renderer;
//static SDL_Texture*  texture;

#define PIXEL_SCALE 9
#define CHAR_SIZE   6
#define WIN_W		64
#define WIN_H		64

//SDL_CreateWindow
//SDL_DestroyWindow

static void set_color(Color color) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
}

void graphics_init() {
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Astro-8", 50, 50, WIN_W * PIXEL_SCALE, WIN_H * PIXEL_SCALE, SDL_WINDOW_OPENGL);

	if (window == nullptr) {
		std::cout << "Failed to create window ( " << SDL_GetError() <<  " )" << std::endl;
		exit(1);
	}

	renderer = SDL_CreateRenderer(window, -1, 0);

	if (renderer == nullptr) {
		SDL_DestroyWindow(window);
		std::cout << "Failed to initialize renderer ( " << SDL_GetError() << " )" << std::endl;
		exit(1);
	}

	/*

	std::string path = SDL_GetBasePath();
	path += "character-set.bmp";
	SDL_Surface* image = SDL_LoadBMP(path.c_str());

	if (image == nullptr) {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		std::cout << "Failed to load character set ( " << SDL_GetError() << " )" << std::endl;
		exit(1);
	}

	texture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);

	if (texture == nullptr) {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		std::cout << "Faild to convert SDL_Surface to SDL_Texture ( " << SDL_GetError() << " )" << std::endl;
		exit(1);
	}
	*/
}

void graphics_plot(int x, int y, Color color) {
	set_color(color);
	SDL_Rect rec = { x * PIXEL_SCALE, y * PIXEL_SCALE, PIXEL_SCALE, PIXEL_SCALE };
	SDL_RenderFillRect(renderer, &rec);
}

//void graphics_draw_char(int index, int pos) {
//	SDL_Rect src = {(index % 13) * CHAR_SIZE, (index / 13) * CHAR_SIZE, CHAR_SIZE, CHAR_SIZE};
//	//SDL_Rect dst = {(pos % 64) * PIXEL_SCALE, (pos / 64) * PIXEL_SCALE, PIXEL_SCALE, PIXEL_SCALE};
//	SDL_Rect dst = { 1, 1, CHAR_SIZE * PIXEL_SCALE, CHAR_SIZE * PIXEL_SCALE};
//	SDL_RenderCopy(renderer, texture, &src, &dst);
//	//SDL_RenderCopy(renderer, texture, nullptr, nullptr);
//}

void graphics_clear(Color color) {
	set_color(color);
	SDL_RenderClear(renderer);
}

void graphics_update() {
	SDL_RenderPresent(renderer);
}

void graphics_close() {
	//SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
