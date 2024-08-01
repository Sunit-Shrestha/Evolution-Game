#include "Organism.h"
#include "Cell.h"

Cell::Cell(Organism *ptr) : belongs_to(ptr) {}

bool Cell::is_placeable(Cell *&cell)
{
	return cell == nullptr;
}

void Cell::place(Cell *&cell)
{
	delete cell;
	cell = this;
	
}

FoodCell::FoodCell() : Cell(nullptr)
{
	type = FOOD;
}

BrainCell::BrainCell(Organism *ptr) : Cell(ptr)
{
	type = BRAIN;
}

AttackCell::AttackCell(Organism *ptr) : Cell(ptr)
{
	type = ATTACK;
}

bool AttackCell::is_placeable(Cell *&cell)
{
	if (cell == nullptr)
		return true;
	if (cell->type == MOUTH || cell->type == BRAIN || cell->type == LEG)
	{
		cell->belongs_to->kill(cell);
	}
	return false;
}

MouthCell::MouthCell(Organism *ptr) : Cell(ptr)
{
	type = MOUTH;
}

bool MouthCell::is_placeable(Cell *&cell)
{
	if (cell == nullptr)
		return true;
	if (cell->type == FOOD)
	{
		return true;
	}
	return false;
}

void MouthCell::place(Cell *&cell)
{
	if (cell != nullptr)
	{
		if (cell->type == FOOD)
		{
		this->belongs_to->energy++;
		}
	}
	delete cell;
	cell = this;
}

Cell *createCell(CellType type, Organism *ptr)
{
	switch (type)
	{
	case FOOD:
		return new FoodCell();
	case BRAIN:
		return new BrainCell(ptr);
	case MOUTH:
		return new MouthCell(ptr);
	case ATTACK:
		return new AttackCell(ptr);
	case LEG:
		return new LegCell(ptr);
	default:
		return nullptr;
	}
}

LegCell::LegCell(Organism *ptr) : Cell(ptr)
{
	type = LEG;
	ptr->num_of_legs++;
}
