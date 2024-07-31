#ifndef CELL_H
#define CELL_H

class Organism;

enum CellType
{
	FOOD,
	BRAIN,
	MOUTH,
	ATTACK,
	LEG
};

class Cell
{
public:
	CellType type;
	Organism *belongs_to;

	Cell(Organism *ptr);

	virtual bool is_placeable(Cell *&cell);
	virtual void place(Cell *&cell);
};

class FoodCell : public Cell
{
public:
	FoodCell();
};

class BrainCell : public Cell
{
public:
	BrainCell(Organism *ptr);
};

class AttackCell : public Cell
{
public:
	AttackCell(Organism *ptr);

	bool is_placeable(Cell *&cell) override;
};

class MouthCell : public Cell
{
public:
	MouthCell(Organism *ptr);

	bool is_placeable(Cell *&cell) override;
	void place(Cell *&cell) override;
};

Cell *createCell(CellType type, Organism *ptr);

#endif // CELL_H
