#include "Vector.h"

Vector::Vector(int x, int y) : x(x), y(y) {}

Vector::Vector(Direction d)
{
	switch (d)
	{
	case NO_MOVE:
		x = 0;
		y = 0;
		break;
	case UP:
		x = 0;
		y = -1;
		break;
	case DOWN:
		x = 0;
		y = 1;
		break;
	case LEFT:
		x = -1;
		y = 0;
		break;
	case RIGHT:
		x = 1;
		y = 0;
		break;
	case UP_LEFT:
		x = -1;
		y = -1;
		break;
	case UP_RIGHT:
		x = 1;
		y = -1;
		break;
	case DOWN_LEFT:
		x = -1;
		y = 1;
		break;
	case DOWN_RIGHT:
		x = 1;
		y = 1;
		break;
	}
}

Vector Vector::operator+(const Vector &other) const
{
	return Vector(x + other.x, y + other.y);
}

Vector Vector::operator-(const Vector &other) const
{
	return Vector(x - other.x, y - other.y);
}

Vector Vector::operator*(int scalar) const
{
	return Vector(x * scalar, y * scalar);
}

Vector Vector::operator/(int scalar) const
{
	return Vector(x / scalar, y / scalar);
}

bool Vector::operator==(const Vector &other) const
{
	return x == other.x && y == other.y;
}

Vector Vector::rotateClockwise() const
{
	return Vector(y, -x);
}

Vector Vector::rotateCounterClockwise() const
{
	return Vector(-y, x);
}

Vector Vector::operator()(Direction d, int times) const
{
	return *this + Vector(d) * times;
}

Vector Vector::operator()(Rotation r) const
{
	switch (r)
	{
	case NO_ROTATION:
		return *this;
	case CLOCKWISE:
		return rotateClockwise();
	case COUNTER_CLOCKWISE:
		return rotateCounterClockwise();
	default:
		return *this;
	}
}
