#ifndef ORGANISM_H
#define ORGANISM_H

#include <vector>

#include "Vector.h"
#include "Cell.h"

class Organism
{
public:
	int id;
	bool alive;
	Vector position;
	std::vector<std::pair<Vector, Cell *>> body;
	int energy;
	int num_of_legs;
	Cell *brain_cell;

	Organism(int x, int y);
	~Organism();

	void kill(Cell *cell);
	void move(Direction move = NO_MOVE, Rotation turn = NO_ROTATION);
	std::vector<std::vector<Cell *>> single_body_positioner(std::vector<std::pair<Vector, Cell *>> _body);
	Vector max_position_finder_2d_matrix(std::vector<std::vector<int>> matrix);
	void evolve(std::vector<std::vector<int>> &list_of_position_value_in_single_organism_world, CellType type);
	void evolution_caller(std::vector<int> list);
};

#endif // ORGANISM_H
