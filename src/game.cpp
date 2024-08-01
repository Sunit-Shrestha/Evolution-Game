#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <algorithm>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "Vector.h"
#include "Cell.h"
#include "Map.h"
#include "Organism.h"

int x_length_of_world = 60;
int y_length_of_world = 60;
int cell_size = 11;
int SCREEN_WIDTH = x_length_of_world * cell_size;
int SCREEN_HEIGHT = y_length_of_world * cell_size;
int FONT_SIZE = 16;
SDL_Color WHITE = {255, 255, 255};
SDL_Color GRAY = {128, 128, 128};
SDL_Color BLACK = {0, 0, 0};

std::vector<std::vector<int>> color_names = {
        {255, 255, 255},
        {255, 255, 0},
        {0, 255, 0},
        {0, 0, 255},
        {165, 42, 42},
        {0, 0, 0}
    };  

std::vector<std::vector<std::vector<int>>> map_colors(Map &map)
{
  std::vector<std::vector<std::vector<int>>> color_array;

  for (auto row : map.grid)
  {
    std::vector<std::vector<int>> color_row;
    for (Cell *cell : row)
    {
			if (cell == nullptr)
			{
				color_row.push_back(color_names[0]);
				continue;
			}
      if (cell->type < color_names.size())
      {
        color_row.push_back(color_names[cell->type + 1]);
      }
      else
      {
        color_row.push_back({255, 0, 0});
      }
    }
    color_array.push_back(color_row);
  }

  return color_array;
}

std::vector<Organism *> organisms = {new Organism(1, 1), new Organism(58, 58)};

void display_opening_screen(SDL_Renderer *renderer, TTF_Font *font, std::string message = "")
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

void start_game(SDL_Renderer *renderer, TTF_Font *font)
{
  std::vector<std::vector<std::vector<int>>> array = map_colors(world);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);
  SDL_Event e;
  bool quit = false;

  // Define movement functions similar to the Python version
  auto go_up = [&]()
  { organisms[0]->move(UP); };
  auto go_down = [&]()
  { organisms[0]->move(DOWN); };
  auto go_left = [&]()
  { organisms[0]->move(LEFT); };
  auto go_right = [&]()
  { organisms[0]->move(RIGHT); };
  auto go_up_right = [&]()
  { organisms[0]->move(UP_RIGHT); };
  auto go_right_down = [&]()
  { organisms[0]->move(DOWN_RIGHT); };
  auto go_down_left = [&]()
  { organisms[0]->move(DOWN_LEFT); };
  auto go_left_up = [&]()
  { organisms[0]->move(UP_LEFT); };
  auto go_clockwise = [&]()
  { organisms[0]->move(NO_MOVE, CLOCKWISE); };
  auto go_anticlockwise = [&]()
  { organisms[0]->move(NO_MOVE, COUNTER_CLOCKWISE); };

  auto go_up2 = [&]()
  { organisms[1]->move(UP); };
  auto go_down2 = [&]()
  { organisms[1]->move(DOWN); };
  auto go_left2 = [&]()
  { organisms[1]->move(LEFT); };
  auto go_right2 = [&]()
  { organisms[1]->move(RIGHT); };
  auto go_up_right2 = [&]()
  { organisms[1]->move(UP_RIGHT); };
  auto go_right_down2 = [&]()
  { organisms[1]->move(DOWN_RIGHT); };
  auto go_down_left2 = [&]()
  { organisms[1]->move(DOWN_LEFT); };
  auto go_left_up2 = [&]()
  { organisms[1]->move(UP_LEFT); };
  auto go_clockwise2 = [&]()
  { organisms[1]->move(NO_MOVE, CLOCKWISE); };
  auto go_anticlockwise2 = [&]()
  { organisms[1]->move(NO_MOVE, COUNTER_CLOCKWISE);};

  auto handle_events = [&]()
  {
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        return false;
      }
    }
    return true;
  };

  auto handle_continuous_keys = [&](const Uint8 *keys)
  {
    if (keys[SDL_SCANCODE_UP] && keys[SDL_SCANCODE_RIGHT])
      go_up_right();
    if (keys[SDL_SCANCODE_RIGHT] && keys[SDL_SCANCODE_DOWN])
      go_right_down();
    if (keys[SDL_SCANCODE_DOWN] && keys[SDL_SCANCODE_LEFT])
      go_down_left();
    if (keys[SDL_SCANCODE_LEFT] && keys[SDL_SCANCODE_UP])
      go_left_up();
    if (keys[SDL_SCANCODE_LEFT] && keys[SDL_SCANCODE_RIGHT])
      go_anticlockwise();
    if (keys[SDL_SCANCODE_DOWN] && keys[SDL_SCANCODE_UP])
      go_clockwise();
    if (keys[SDL_SCANCODE_UP])
      go_up();
    if (keys[SDL_SCANCODE_DOWN])
      go_down();
    if (keys[SDL_SCANCODE_RIGHT])
      go_right();
    if (keys[SDL_SCANCODE_LEFT])
      go_left();
		if (keys[SDL_SCANCODE_M])
		{
			if (organisms[0]->energy > 0)
			{
				std::vector<int> numbers = get_user_input(renderer, font);
				organisms[0]->evolution_caller(numbers);
			}
			else
			{
				evolve_failed(renderer, font);
			}
		}
  };

  auto handle_continuous_keys2 = [&](const Uint8 *keys)
  {
    if (keys[SDL_SCANCODE_W] && keys[SDL_SCANCODE_D])
      go_up_right2();
    if (keys[SDL_SCANCODE_D] && keys[SDL_SCANCODE_S])
      go_right_down2();
    if (keys[SDL_SCANCODE_S] && keys[SDL_SCANCODE_A])
      go_down_left2();
    if (keys[SDL_SCANCODE_A] && keys[SDL_SCANCODE_W])
      go_left_up2();
    if (keys[SDL_SCANCODE_A] && keys[SDL_SCANCODE_D])
      go_anticlockwise2();
    if (keys[SDL_SCANCODE_S] && keys[SDL_SCANCODE_W])
      go_clockwise2();
    if (keys[SDL_SCANCODE_W])
      go_up2();
    if (keys[SDL_SCANCODE_S])
      go_down2();
    if (keys[SDL_SCANCODE_D])
      go_right2();
    if (keys[SDL_SCANCODE_A])
      go_left2();
		if (keys[SDL_SCANCODE_E])
		{
			if (organisms[1]->energy > 0)
			{
				std::vector<int> numbers = get_user_input(renderer, font);
				organisms[1]->evolution_caller(numbers);
			}
			else
			{
				evolve_failed(renderer, font);
			}
		}
  };

  while (!quit)
  {
    quit = !handle_events();
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    handle_continuous_keys(keys);
    handle_continuous_keys2(keys);
		std::vector<std::vector<std::vector<int>>> array = map_colors(world);
    draw_array(renderer, array);
    SDL_Delay(100);
  }
}

int main()
{
	for (auto organism : organisms) 
	{
		world.place_organism(*organism);
	}

  std::vector<int> no_of_success;
  std::srand(std::time(0));
	
  for (int i = 0; i < 5; ++i)
  {
    int x = std::rand() % x_length_of_world;
    int y = 20 + (std::rand() % 21);
		if (world[Vector(x, y)] == nullptr)
    	world[Vector(x, y)] = new FoodCell();
  }

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    return -1;
  }

  if (TTF_Init() == -1)
  {
    std::cerr << "TTF could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
    return -1;
  }

  SDL_Window *window = SDL_CreateWindow("Opening Screen Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == nullptr)
  {
    std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
    return -1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == nullptr)
  {
    std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
    return -1;
  }

  TTF_Font *font = TTF_OpenFont("/usr/share/fonts/TTF/Arial.TTF", FONT_SIZE);
  if (font == nullptr)
  {
    std::cerr << "Failed to load font! TTF_Error: " << TTF_GetError() << std::endl;
    return -1;
  }

	for (auto organism : organisms)
	{			
		if (organism->energy > 0)
		{
			std::vector<int> numbers = get_user_input(renderer, font);
			organism->evolution_caller(numbers);
		}
		else
		{
			evolve_failed(renderer, font);
		}
	}

  start_game(renderer, font);

  TTF_CloseFont(font);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_Quit();
  SDL_Quit();

	for (auto organism : organisms)
	{
		delete organism;
	}
	organisms.clear();

	return 0;
}
