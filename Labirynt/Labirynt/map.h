#pragma once
#include <vector>
#include "TileType.h"
#include "Position.h"

typedef unsigned int size;

class Map
{
public :
	Map(const size width, const size height);
	Map(const size width, const size height, std::vector<TileType> tiles);

	TileType getTile(const size index) const;
	TileType getTile(const size x, const size y) const;
	TileType getTile(const Position &) const;
	void     setTile(const size index, const TileType);
	void     setTile(const size x, const size y, const TileType);
	void     setTile(const Position &, const TileType);

	size getWidth() const; //pobierz szerokosc
	size getHeight() const; //pobierz wysokosc

protected :
	size positionIndex(const size x, const size y) const;

	std::vector<TileType> tiles; //pola mapy (mapa) 
	const size width; //szerokosc
	const size height; //wysokosc

};