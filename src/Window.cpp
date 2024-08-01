#include <iostream>

#include "Window.h"
#include "Map.h"

int cell_size = 11;
int SCREEN_WIDTH = world_columns * cell_size;
int SCREEN_HEIGHT = world_rows * cell_size;
SDL_Color WHITE = {255, 255, 255};
SDL_Color GRAY = {128, 128, 128};
SDL_Color BLACK = {0, 0, 0};

void display_opening_screen(SDL_Renderer *renderer, TTF_Font *font, std::string message)
{
  SDL_SetRenderDrawColor(renderer, WHITE.r, WHITE.g, WHITE.b, 255);
  SDL_RenderClear(renderer);

  SDL_Surface *title_surface = TTF_RenderText_Solid(font, "K_Up/W: up, K_Down/S: down, K_Left/A: left, K_Right/D: right", BLACK);
  if (!title_surface)
  {
    std::cerr << "Failed to create title surface: " << TTF_GetError() << std::endl;
    return;
  }
  SDL_Texture *title_texture = SDL_CreateTextureFromSurface(renderer, title_surface);
  SDL_Rect title_rect = {(SCREEN_WIDTH - title_surface->w) / 2, 50, title_surface->w, title_surface->h};
  SDL_RenderCopy(renderer, title_texture, NULL, &title_rect);

  SDL_Surface *title_surface2 = TTF_RenderText_Solid(font, "up and down at once for clockwise rotation, right and left at once for anticlockwise rotation", BLACK);
  if (!title_surface2)
  {
    std::cerr << "Failed to create title surface2: " << TTF_GetError() << std::endl;
    return;
  }
  SDL_Texture *title_texture2 = SDL_CreateTextureFromSurface(renderer, title_surface2);
  SDL_Rect title_rect2 = {(SCREEN_WIDTH - title_surface2->w) / 2, 90, title_surface2->w, title_surface2->h};
  SDL_RenderCopy(renderer, title_texture2, NULL, &title_rect2);

  SDL_Surface *instructions_surface = TTF_RenderText_Solid(font, "Enter a list of numbers separated by spaces for evolution of left then right:", BLACK);
  if (!instructions_surface)
  {
    std::cerr << "Failed to create instructions surface: " << TTF_GetError() << std::endl;
    return;
  }
  SDL_Texture *instructions_texture = SDL_CreateTextureFromSurface(renderer, instructions_surface);
  SDL_Rect instructions_rect = {(SCREEN_WIDTH - instructions_surface->w) / 2, 200, instructions_surface->w, instructions_surface->h};
  SDL_RenderCopy(renderer, instructions_texture, NULL, &instructions_rect);

	SDL_Color text_color = BLACK;
	if (message == "")
	{
		message = "Enter the numbers";
		text_color = GRAY;
	}
  SDL_Surface *evol_surface = TTF_RenderText_Solid(font, message.c_str(), text_color);
  if (!evol_surface)
  {
    std::cerr << "Failed to create evolve surface: " << TTF_GetError() << std::endl;
		SDL_FreeSurface(title_surface);
		SDL_DestroyTexture(title_texture);
		SDL_FreeSurface(title_surface2);
		SDL_DestroyTexture(title_texture2);
		SDL_FreeSurface(instructions_surface);
		SDL_DestroyTexture(instructions_texture);
    return;
  }
  SDL_Texture *evol_texture = SDL_CreateTextureFromSurface(renderer, evol_surface);
  SDL_Rect evol_rect = {(SCREEN_WIDTH - evol_surface->w) / 2, 250, evol_surface->w, evol_surface->h};
	SDL_RenderCopy(renderer, evol_texture, NULL, &evol_rect);

	SDL_SetRenderDrawColor(renderer, BLACK.r, BLACK.g, BLACK.b, 255);
	int border_width = 2;
	int box_width = 300;
	int box_height = evol_surface->h;
	int box_width_gap = 100;
  SDL_Rect borderRect = {(SCREEN_WIDTH - box_width - box_width_gap) / 2, 250, box_width + box_width_gap, box_height};
	SDL_RenderDrawLine(renderer, borderRect.x, borderRect.y, borderRect.x + borderRect.w, borderRect.y);
	SDL_RenderDrawLine(renderer, borderRect.x, borderRect.y + borderRect.h, borderRect.x + borderRect.w, borderRect.y + borderRect.h);
	SDL_RenderDrawLine(renderer, borderRect.x, borderRect.y, borderRect.x, borderRect.y + borderRect.h);
	SDL_RenderDrawLine(renderer, borderRect.x + borderRect.w, borderRect.y, borderRect.x + borderRect.w, borderRect.y + borderRect.h);


  SDL_RenderPresent(renderer);

  SDL_FreeSurface(title_surface);
  SDL_DestroyTexture(title_texture);
  SDL_FreeSurface(title_surface2);
  SDL_DestroyTexture(title_texture2);
  SDL_FreeSurface(instructions_surface);
  SDL_DestroyTexture(instructions_texture);
	SDL_FreeSurface(evol_surface);
  SDL_DestroyTexture(evol_texture);
}

std::vector<int> get_user_input(SDL_Renderer *renderer, TTF_Font *font)
{
	
  SDL_Rect input_box = {(SCREEN_WIDTH - 300) / 2, 250, 300, 40};
  std::string input_text = "";
	display_opening_screen(renderer, font, input_text);
	SDL_Event e;
  bool input_active = true;

  while (input_active)
  {
    while (SDL_PollEvent(&e))
    {
      if (e.type == SDL_QUIT)
      {
        SDL_Quit();
        exit(0);
      }
			else if (e.type == SDL_KEYDOWN)
      {
        if (e.key.keysym.sym == SDLK_RETURN)
        {
					input_active = false;
        }
        else if (e.key.keysym.sym == SDLK_BACKSPACE)
        {
					if (input_text.length() > 0)
          	input_text.pop_back();
        }
        else if (e.key.keysym.sym == SDLK_SPACE)
        {
          input_text += ' ';
        }
        else
        {
          input_text += e.key.keysym.sym;
        }
      }
    }

    SDL_SetRenderDrawColor(renderer, WHITE.r, WHITE.g, WHITE.b, 255);
    SDL_RenderClear(renderer);
    display_opening_screen(renderer, font, input_text);
  }

	std::vector<int> numbers;
	std::string number;
	bool negative = false;
	for (char c : input_text)
	{
		if (c == '-')
		{
			negative = true;
		}
		else if (c != ' ')
		{
			number = c;
			numbers.push_back(negative ? -std::stoi(number): std::stoi(number));
			negative = false;
		}
	}
	return numbers;

}

void evolve_failed(SDL_Renderer *renderer, TTF_Font *font)
{
	display_opening_screen(renderer, font, "Evolution failed. Press any key to exit.");
	SDL_Event e;
	while (true)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				SDL_Quit();
				exit(0);
			}
			else if (e.type == SDL_KEYDOWN)
			{
				return;
			}
		}
	}
}

void draw_array(SDL_Renderer *renderer, std::vector<std::vector<std::vector<int>>> array)
{
  for (std::size_t i = 0; i < array.size(); ++i)
  {
    for (std::size_t j = 0; j < array[i].size(); ++j)
    {
      SDL_SetRenderDrawColor(renderer, array[i][j][0], array[i][j][1], array[i][j][2], 255);
      SDL_Rect cell_rect = {static_cast<int>(j * cell_size), static_cast<int>(i * cell_size), cell_size, cell_size};
      SDL_RenderFillRect(renderer, &cell_rect);
    }
  }
  SDL_RenderPresent(renderer);
}