#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>

void display_opening_screen(SDL_Renderer *renderer, TTF_Font *font, std::string message = "");
std::vector<int> get_user_input(SDL_Renderer *renderer, TTF_Font *font);
void evolve_failed(SDL_Renderer *renderer, TTF_Font *font);
void draw_array(SDL_Renderer *renderer, std::vector<std::vector<std::vector<int>>> array);

extern int cell_size;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern SDL_Color WHITE;
extern SDL_Color GRAY;
extern SDL_Color BLACK;

#endif // WINDOW_H