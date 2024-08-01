#ifndef VECTOR_H
#define VECTOR_H

enum Direction
{
	NO_MOVE,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	UP_LEFT,
	UP_RIGHT,
	DOWN_LEFT,
	DOWN_RIGHT
};

enum Rotation
{
	NO_ROTATION,
	CLOCKWISE,
	COUNTER_CLOCKWISE
};

class Vector
{
public:
	int x;
	int y;

	Vector(int x, int y);

	Vector(Direction d);

	Vector operator+(const Vector &other) const;
	Vector operator-(const Vector &other) const;
	Vector operator*(int scalar) const;
	Vector operator/(int scalar) const;
	bool operator==(const Vector &other) const;
	Vector rotateClockwise() const;
	Vector rotateCounterClockwise() const;
	Vector operator()(Direction d, int times = 1) const;
	Vector operator()(Rotation r) const;
};

#endif // VECTOR_H
