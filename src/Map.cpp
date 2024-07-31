#include "Vector.h"
#include "Cell.h"
#include "Organism.h"
#include "Map.h"

int world_rows = 60;
int world_columns = 60;

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

Map world(world_rows, world_columns);
