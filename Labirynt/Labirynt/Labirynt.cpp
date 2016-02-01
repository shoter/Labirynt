// Labirynt.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "map.h"
#include "MapFileIO.h"
#include "Astar.h"
#include "MapStreamIO.h"
#include "Labirynt.h"
#include <cstdlib>

void printHelp()
{
	std::cout << "Labirynt.exe" << std::endl
		<< "? or help - to display this help" << std::endl
		<< "[inputfilePath] [outputfilePath] - to run program" << std::endl
		<< "[width] [height] [walls] - to run program" << std::endl;
}

//argc - ilosc argumentow
//argv - tablica z argumentami [0] to nazwa programu
MapIO* processArgs(int argc, char **argv)
{
	switch (argc)
	{
	case 1: //pierwszym argumenetem jest nazwa pliu ktory wykonujemy
		return new MapStreamIO();
	case 2:
		if (strcmp(argv[1], "?" )|| strcmp(argv[1], "help")) //strcmp sprawdza czy argument jest rowny temu co po prawej
			printHelp();
		break;
	case 3:
	{
		std::string inputFile = argv[1];
		std::string outputFile = argv[2];
		return new MapFileIO(inputFile, outputFile);
	}
	}
	return nullptr;
}


int main(int argc, char ** argv)
{
	MapIO *mapIO;
	try
	{
		//pobranie odpowiedniej klasy generujacej mape na podstawie argumentów.
		mapIO = processArgs(argc, argv);

		//Moze sie zdarzyc ze ktos wyswietla pomoc. Wtedy zwracany jest nullptr;
		if (mapIO != nullptr)
		{
			//wczytujemy mape
			Map *map = mapIO->load();
			//inicjalizujemy algorytm A*
			Astar astar;
			//Zmienne pomocniczne.
			//Przechowuje najkrotsza sciezke
			Path* shortestPath = nullptr;
			//iteruje po calej szerokosci mapy
			for (size x = 0; x < map->getWidth(); ++x)
			{
				if (map->getTile(x, 0) == TileType::Occupied)
					continue; //kontynnuuj jesli jest murek

				//szuka najkrotszej sciezki z pozycji x u gory planszy
				Path * path = astar.findPath(Position(x, 0), map);
				if (path != nullptr)
				{
					//jesli znalazlo sciezke badz sciezki jeszcze nie bylo
					if (shortestPath == nullptr || (shortestPath->path.size() > path->path.size()))
					{
						delete shortestPath; //na poczatku jest inicjalizowane nullptr, wiec nawet pierwsze usuniecie sciezki nie robi nic zlego
						//usuwanie nullptr == nic sie nie dzieje :)
						shortestPath = path;
					}
					else
						delete path;
				}
			}
			//Zapisujemy wynik
			mapIO->save(shortestPath);
			delete map;
			delete shortestPath;
		}

		delete mapIO;
	}
	//Zwykla obsluga wyjatkow. Na wyjatkowe sytuacje :)
	catch (std::exception e)
	{
		std::cout << "Exception : " << e.what() << std::endl;
		system("pause");
		delete mapIO;
		throw; //wrzucam tutaj ten sam wyjatek
	}
	return 0;
}

