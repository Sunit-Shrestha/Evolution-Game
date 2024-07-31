#ifndef MAP_H
#define MAP_H

#include <vector>

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
};

extern Map world;

#endif // MAP_H
