#pragma once
#include <vector>
#include "Position.h"

struct Path
{
	std::vector<Position> path;

	std::string toString() const;

};