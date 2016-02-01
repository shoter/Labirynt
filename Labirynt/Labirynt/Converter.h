#pragma once
#include "TileType.h"
#include "Astar.h"

class Converter
{
public:
	static TileType convertToTileType(const char);
	static char convertToChar(const TileType);
	static char convertToDisplayDebug(const TileType);
};
