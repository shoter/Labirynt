#include "stdafx.h"
#include "MapFileIO.h"
#include <fstream>
#include <exception>
#include "Converter.h"
using std::ios;

MapFileIO::MapFileIO(const std::string & inputFile, const std::string & outputFile)
	:inputFile(inputFile), outputFile(outputFile)
{
}
Map* MapFileIO::load()
{
	size width, height;
	std::ifstream file;
	//otwiera plik z flaga pliku INput
	file.open(inputFile, ios::in);
	//nie ma file.close(), dlaczego? O boze, swiat sie rozleci na kawalki jak nie zamkne pliku xD
	//wcale tak nie jest
	//file uzywa metody zwanej RAII (Resource Acquisition Is Initialization)
	//w skrocie, jak sie wywoluje destruktor takiego obiektu to ZWALNIA wszystko. sprzata po sobie
	//wg standardu C++ (27.8.1.2) nie trzeba zamykac

	Map * map;

	if (file.is_open())
	{
		file >> height;
		file >> width;


		map = new Map(width, height);

		std::string mapString;
		std::string line;
		for (unsigned int i = 0;i < height; ++i)
		{
			file >> line;
			mapString += line;
		}

		//Petla zmienia string na tile i przypisuje go do danego fragmentu mapy
		for (unsigned int i = 0;i < mapString.size(); ++i)
		{
			TileType tile = Converter::convertToTileType(mapString.at(i)); //zmiana chara na tileType
			map->setTile(i, tile); //przypisuje do danego fragmentu mapy
		}

	}
	else
	{
		throw std::exception("File not found");
	}

	return map;
}

void MapFileIO::save(const Path *path)
{
	//otwieramy plik z flaga zapisu (OUTput) i czyscimy zawartosc pliku (TRUNCuate)
	std::ofstream file = std::ofstream(outputFile, ios::ios_base::out | ios::ios_base::trunc);
	if (path == nullptr) //brak sciezki
	{
		file << "nie" << std::endl;
	}
	else //mamy sciezke
	{
		file << "tak ";
		file << path->path[0].x + 1 << " "; //wypisuje wsporlzedna xowa pierwszego kroku w sciezce. dodajemy 1 poniewaz w C++ numerujemy od 0
		file << path->toString() << std::endl;
	}
}
