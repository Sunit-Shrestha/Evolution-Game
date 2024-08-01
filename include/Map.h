#ifndef MAP_H
#define MAP_H

#include <vector>

#include "Vector.h"

class Cell;
class Organism;

class Map
{
public:
	std::vector<std::vector<Cell *>> grid;

	Map(int rows, int columns);

	bool place_organism(Organism &organism);
	void remove_organism(Organism &organism);
	Cell *&operator[](Vector v);
	std::size_t size();
	~Map();
	std::vector<std::vector<std::vector<int>>> map_colors();
};

extern int world_rows;
extern int world_columns;
extern Map world;

#endif // MAP_H
