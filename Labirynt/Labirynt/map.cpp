#include "stdafx.h"
#include "map.h"

Map::Map(const size width, const size height)
	:width(width), height(height)
{
	tiles = std::vector<TileType>(width * height);
}

Map::Map(const size width, const size height, std::vector<TileType> tiles)
	:Map(width, height)
{
	this->tiles = tiles;
}

TileType Map::getTile(const size index) const
{
	return tiles.at(index);
}

TileType Map::getTile(const size  x, const size y) const
{
	size index = positionIndex(x, y);
	return getTile(index);
}

TileType Map::getTile(const Position &pos) const
{
	return getTile(pos.x, pos.y);
}

void Map::setTile(const size index, const TileType tile)
{
	tiles[index] = tile;
}

void Map::setTile(const size x, const size y, const TileType tile)
{
	size index = positionIndex(x, y);
	setTile(index, tile);
}

void Map::setTile(const Position & pos, const TileType tile)
{
	setTile(pos.x, pos.y, tile);
}

size Map::getWidth() const
{
	return width;
}

size Map::getHeight() const
{
	return height;
}

size Map::positionIndex(const size x, const size y) const
{
	return y * width + x;
}
