#include "Vector.h"
#include "Cell.h"
#include "Organism.h"
#include "Map.h"

int world_rows = 60;
int world_columns = 60;
std::vector<std::vector<int>> color_names = {
	{255, 255, 255},
	{255, 255, 0},
	{0, 255, 0},
	{0, 0, 255},
	{165, 42, 42},
	{0, 0, 0}
}; 

Map::Map(int rows, int columns)
{
	for (int i = 0; i < rows; i++)
	{
		std::vector<Cell *> temp(columns, nullptr);
		grid.push_back(temp);
	}
}

bool Map::place_organism(Organism &organism)
{
	for (int i = 0; i < organism.body.size(); i++)
	{
		Vector pos = organism.body[i].first + organism.position;
		Cell *cell = organism.body[i].second;
		if (pos.x < 0 || pos.y < 0 || pos.x >= world_columns || pos.y >= world_rows)
		{
			return false;
		}
		if (cell->type == ATTACK && !cell->is_placeable((*this)[pos]))
		{
			return false;
		}
	}

	for (int i = 0; i < organism.body.size(); i++)
	{
		Vector pos = organism.body[i].first + organism.position;
		Cell *cell = organism.body[i].second;
		if (pos.x < 0 || pos.y < 0 || pos.x >= world_columns || pos.y >= world_rows)
		{
			return false;
		}
		if (cell->type != ATTACK && !cell->is_placeable((*this)[pos]))
		{
			return false;
		}
	}

	for (int i = 0; i < organism.body.size(); i++)
	{
		Vector pos = organism.body[i].first + organism.position;
		Cell *cell = organism.body[i].second;
		cell->place((*this)[pos]);
	}
	return true;
}

void Map::remove_organism(Organism &organism)
{
	for (int i = 0; i < organism.body.size(); i++)
	{
		Vector pos = organism.body[i].first + organism.position;
		(*this)[pos] = nullptr;
	}
}

Cell *&Map::operator[](Vector v)
{
	return grid[v.y][v.x];
}

std::size_t Map::size()
{
	return grid.size();
}

Map::~Map()
{
	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[i].size(); j++)
		{
			if (grid[i][j] != nullptr && grid[i][j]->belongs_to == nullptr)
			{
				delete grid[i][j];
			}
		}
	}
}

std::vector<std::vector<std::vector<int>>> Map::map_colors()
{
  std::vector<std::vector<std::vector<int>>> color_array;

  for (auto row : grid)
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

Map world(world_rows, world_columns);
