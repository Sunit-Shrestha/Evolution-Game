#include <iostream>

#include "Vector.h"
#include "Cell.h"
#include "Organism.h"
#include "Map.h"

int counter = 0;

Organism::Organism(int x, int y) : energy(1), position(Vector(x, y)), alive(true), num_of_legs(0)
{
	id = counter;
	counter++;
	body = {
			{{0, 0}, new BrainCell(this)},
			{{0, -1}, new MouthCell(this)},
			{{0, 1}, new MouthCell(this)},
			{{-1, 0}, new AttackCell(this)},
			{{1, 0}, new LegCell(this)}};
}

Organism::~Organism()
{
	for (auto pair : body)
	{
		delete pair.second;
	}
}

void Organism::kill(Cell *cell)
{
	if (cell->type == BRAIN)
	{
		alive = false;
		for (auto pair : body)
		{
			Vector pos = pair.first + position;
			world[pos] = new FoodCell();
		}
		return;
	}
	for (int i = 0; i < body.size(); i++)
	{
		if (body[i].second == cell)
		{
			if (cell->type == LEG)
			{
				num_of_legs--;
			}
			Vector pos = body[i].first + position;
			body.erase(body.begin() + i);
			delete cell;
			world[pos] = new FoodCell();
			break;
		}
	}
}

void Organism::move(Direction move, Rotation turn)
{
	if (!alive)
		return;

	world.remove_organism(*this);
	Vector old_position = position;
	std::vector<std::pair<Vector, Cell *>> old_body = body;

	position = position(move);
	for (auto &pair : body)
	{
		pair.first = pair.first(turn);
	}

	bool invalid_move = !world.place_organism(*this);
	if (invalid_move)
	{
		body = old_body;
		position = old_position;
		world.place_organism(*this);
	}
}

std::vector<std::vector<Cell *>> Organism::single_body_positioner(std::vector<std::pair<Vector, Cell *>> _body)
{
	std::vector<std::vector<Cell *>> single_organism_world(9, std::vector<Cell *>(9, nullptr));

	for (auto element : _body)
	{
		Vector new_element_position = element.first + Vector(4, 4);
		single_organism_world[new_element_position.y][new_element_position.x] = element.second;
	}

	return single_organism_world;
}

Vector Organism::max_position_finder_2d_matrix(std::vector<std::vector<int>> matrix)
{
	int max_value = -10000;
	Vector max_position(0, 0);
	for (int i = 0; i < matrix.size(); ++i)
	{
		for (int j = 0; j < matrix[i].size(); ++j)
		{
			int value = matrix[i][j];
			if (value > max_value)
			{
				max_value = value;
				max_position = Vector(j, i);
			}
		}
	}

	return max_position;
}

void Organism::evolve(std::vector<std::vector<int>> &list_of_position_value_in_single_organism_world, CellType type)
{
	world.remove_organism(*this);
	const std::vector<std::pair<Vector, Cell *>> old_body = body;
	std::vector<std::vector<Cell *>> single_body_world = single_body_positioner(body);

	for (int i = 1; i < 8; ++i)
	{
		for (int j = 1; j < 8; ++j)
		{
			if (single_body_world[i][j] != 0)
			{
				list_of_position_value_in_single_organism_world[i - 1][j - 1] = 0;
			}
			bool all_neighbors_empty = true;
			for (int di = -1; di <= 1; ++di)
			{
				for (int dj = -1; dj <= 1; ++dj)
				{
					if (di == 0 && dj == 0)
						continue;
					if (single_body_world[i + di][j + dj] != 0)
					{
						all_neighbors_empty = false;
						break;
					}
				}
				if (!all_neighbors_empty)
					break;
			}
			if (all_neighbors_empty)
			{
				list_of_position_value_in_single_organism_world[i - 1][j - 1] = 0;
			}
		}
	}

	Vector position_to_add_type = max_position_finder_2d_matrix(list_of_position_value_in_single_organism_world) + Vector(-3, -3);
	for (int i = 0; i < body.size(); i++)
	{
		if (body[i].first == position_to_add_type)
		{
			return;
		}
	}
	Cell *cell_to_add = createCell(type, this);

	body.push_back({position_to_add_type, cell_to_add});
	world.place_organism(*this);
	energy--;
}

void Organism::evolution_caller(std::vector<int> list)
{
  int num_chunks = list.size() / 3;
  for (int i = 0; i < num_chunks; ++i)
  {

    std::vector<std::vector<int>> matrix(7, std::vector<int>(7, 0));
    matrix[3 + list[1 + i * 3]][3 + list[0 + i * 3]] = 1;
    evolve(matrix, CellType(list[2 + i * 3]));
  }
}
