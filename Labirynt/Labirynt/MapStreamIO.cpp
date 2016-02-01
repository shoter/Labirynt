#include "stdafx.h"
#include "MapStreamIO.h"
#include <exception>
#include "Converter.h"
Map * MapStreamIO::load()
{
	size x, y;

	Map * map;

	std::cin >> y;
	std::cin >> x;


	map = new Map(x, y);

	std::string mapString;
	std::string line;
	for (size i = 0;i < y; ++i)
	{
		std::cin >> line;
		mapString += line;
	}
	//Petla zmienia string na tile i przypisuje go do danego fragmentu mapy
	for (unsigned int i = 0;i < mapString.size(); ++i)
	{
		TileType tile = Converter::convertToTileType(mapString.at(i));
		map->setTile(i, tile);
		
	}

	return map;
}

void MapStreamIO::save(const Path *path)
{
	if (path == nullptr)
	{
		std::cout << "nie" << std::endl;
	}
	else
	{
		std::cout << "tak ";
		std::cout << path->path[0].x + 1 << " ";
		std::cout << path->toString() << std::endl;
	}
}
