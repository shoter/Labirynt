#pragma once
typedef unsigned int size;

struct Position
{
	size x;
	size y;

	Position(int x, int y) :x(x), y(y) {}
	

	bool operator ==(const Position &rhm) const
	{
		return
			x == rhm.x
			&&
			y == rhm.y;
	}

	bool operator !=(const Position &rhm) const
	{
		return !(*this == rhm);
	}
};