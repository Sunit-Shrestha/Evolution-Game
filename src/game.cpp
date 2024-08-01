#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <algorithm>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <numeric>
#include <string>

#include "Vector.h"
#include "Cell.h"
#include "Map.h"
#include "Organism.h"
#include "Window.h"

int FONT_SIZE = 16;

std::vector<Organism *> organisms = {new Organism(1, 1), new Organism(58, 58)};

void start_game(SDL_Renderer *renderer, TTF_Font *font)
{
  std::vector<std::vector<std::vector<int>>> array = world.map_colors();
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

	int org1_time = 120 / organisms[0]->num_of_legs;
	int org2_time = 120 / organisms[1]->num_of_legs;
	int interval = std::gcd(org1_time, org2_time);
	int count1 = 0;
	int count2 = 0;

  while (!quit)
  {
    quit = !handle_events();
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
		if (count1 * interval == org1_time) 
		{
	    handle_continuous_keys(keys);
			count1 = 0;
		}
		if (count2 * interval == org2_time)
		{
	    handle_continuous_keys2(keys);
			count2 = 0;
		}
		org1_time = 120 / organisms[0]->num_of_legs;
		org2_time = 120 / organisms[1]->num_of_legs;
		interval = std::gcd(org1_time, org2_time);
		std::vector<std::vector<std::vector<int>>> array = world.map_colors();
    draw_array(renderer, array);
		count1++;
		count2++;
    SDL_Delay(interval);
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
	
  for (int i = 0; i < 20; ++i)
  {
    int x = std::rand() % world_columns;
    int y = std::rand() % world_rows;
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
