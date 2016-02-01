#include "stdafx.h"
#include "Astar.h"
#include <math.h>

size Astar::mapWidth = 0;
size Astar::mapHeight = 0;

Astar::Astar()
{
}


Astar::~Astar()
{
}


long Astar::NodeHash::operator() (const Position& key)const
{
	return key.x + key.y * mapWidth;
}


bool Astar::NodeEqual::operator() (const Position& x, const Position& y) const {
	if (x.x == y.x && x.y == y.y)
		return true;
	return false;
}

//aha to jest kurwa nie do ogarniecia na podstawie tego kodu xD.
//tak dawno byl pisany zeeee ja nie moge XD.
//modlilem sie o to ze zmiana pod twoj program zadziala
//i zadzialala XD. legitna modlitwa XD
Path* Astar::findPath(Position begin,Map *map)
{
	mapWidth = map->getWidth(); //used in NodeHash <- co to jest nodeHash? a wiesz ze nie wiem :P. Uzywana jest tutaj unordered_map i pewnie tam jest uzywany has
	//do szybkiego dostepu do elementow. Taka optymalizacja...chyba...dawno to pisalem
	mapHeight = map->getHeight();


	std::vector<Node *> closedSet; //Czytaj wiki co to jest XD
	std::list<Node *>	openSet; // tu tez wiki XD, tu sa chyba node'y do przeanalizowania ktore sa w kolejce
	std::unordered_map<Position, Node*, NodeHash, NodeEqual> cameFrom; // tu tez wiki, ale obstawiam ze to sa przeanalizowane sciezki, ciezko powiedziec XD

	//	std::unordered_map<sf::Vector2i, Node *, Astar::Node::vectorCompare> cameFrom; //unordered_map acts like coordinates
	Position directions[4] = { Position(0, 1), Position(0, -1),
		Position(1, 0), Position(-1, 0) }; //mozliwe kierunki w ktorych porusza sie nasz ktosiek

	openSet.push_back(new Node(begin));  //dodajemy poczatek jako node do analizy
	(*openSet.begin())->f_score = (*openSet.begin())->estimate_cost(mapHeight); //liczymy jego koszt dostania sie do niego

	while (!openSet.empty())
	{
		Node *current = *openSet.begin(); //bierzemy pierwszy node. Powinien(?) miec najnizszy koszt
		if (current->position.y == mapHeight - 1 && map->getTile(current->position) != TileType::Occupied) //jesli jestesmy na koncu i nie jest to murek to dotarlismy do celu XD
		{
			Node *endNode = new Node(current->position); //nie wiem po co to a czemu nie uzywamy currenta. Kod jest stary. Lepiej nic nie dotykac.ŻODYN NI WI CO SIE TU NAPRAWDE DZIEJE :DD
			Path *path = Node::reconstructPath(cameFrom, new Path, endNode, begin); //rekonstrukcja sciezki. pamietaj ze cameFrom zawiera informacje o wszystkich odwiedzonych tile'ach. Nie ma tam de facto sciezki
			delete endNode;
			for (Node *node : openSet)
				delete node;
			for (Node *node : closedSet)
				delete node;

			return path;
		}
		//usuwamy pierwszy element bo juz go wyciagnelismy
		openSet.pop_front(); //delete first element in List.
		closedSet.push_back(current); //wkladamy go do juz przeanalizowanych

		for (Position direction : directions) //jedziemy po wszystkich kierunkach
		{
			Position nPosition = Position(current->position.x + direction.x,
				current->position.y + direction.y); //position of neighbour

			if (nPosition.x < 0 || nPosition.x >= mapWidth ||
				nPosition.y < 0 || nPosition.y >= mapHeight) continue; //tile out of bounds

			TileType tile = map->getTile(current->position);
			if (tile == TileType::Occupied) continue; // Tile is not passable. Continue

			float tentative_g_score = current->g_score + current->estimate_cost(mapHeight); //to jest cos, nie wiem trzeba sprawdzic wiki :P. Koszt dotarcia do tego node'a

			auto existCF = cameFrom.find(nPosition); //does it exist in CameFrom
			if (existCF != cameFrom.end()) //found that neighbour exists in CameFrom
				if (tentative_g_score >= existCF->second->g_score)
					continue;

			bool existOS = false; //true if exists in openset, otherwise false. Prawdziwe jesli istnieje w kolejce (openset)
			Node *neighbour = nullptr;
			for (Node * X : openSet)
				if (X->position.x == nPosition.x && X->position.y == nPosition.y)
				{
					neighbour = X;
					existOS = true;
					break;
				}

			if (!existOS)
				neighbour = new Node(nPosition); //jesli nie istnieje w opensecie to tworzymy node
			//lepszy wynik punktowy rozumiem przez to ze koszt dotarcia tutaj jest mniejszy od sasiada
			//o widzisz, tutaj jest porownanie :D
			if (!existOS || tentative_g_score < neighbour->g_score) //tutaj jest przypisanie nowych kosztow
			{
				// <gdzie jest <- position, node -> skad przyszedl>
				std::pair<Position, Node*> from(neighbour->position, current);
				//sprawdzamy czy juz istnieje w cameFrom
				auto exist = cameFrom.find(from.first);
				//exist to std::pair<position, node*>
				if (exist != cameFrom.end()) //jesli sie odnalazlo :D
					exist->second = current; //jesli dochodzimy tutaj mniejszym kosztem to updatujemy nowy kierunek z ktorego przyszedl. Dajemy tutaj ten wlasnie kierunek
				else
					cameFrom.insert(from); //tutaj dajemy gdy takiego kierunku jeszcze nie bylo.

				neighbour->g_score = tentative_g_score;
				neighbour->f_score = tentative_g_score + neighbour->estimate_cost(mapHeight);
				if (!existOS) //jesli nie istnial w kolejce to go tam dodaje
				{
					bool inserted = false;
					if (!openSet.empty())
					{
						auto it = openSet.begin();
						while (it != openSet.end())
						{
							Node *current = *it;
							if (*current >= neighbour) //zawsze musi go dodac tak zeby element przed nim (jesli istnieje) mial koszt mniejszy niz on. I element po nim (jesli istnieje) mial koszt wiekszy.
							{
								openSet.insert(it, neighbour);
								inserted = true;
								break;
							}
							it++;
						}
					}

					if (inserted == false)
						openSet.push_back(neighbour);
				}
			}
		}
	}

	for (Node *node : openSet)
		delete node;
	for (Node *node : closedSet)
		delete node;

	return nullptr;
}


Path* Astar::Node::reconstructPath(std::unordered_map<Position, Node*, NodeHash, NodeEqual> &came_from, Path* path, Node *currentNode, Position begin)
{
	//rekonstrujemy sciezke. Jest to rekurencyjna funkcja
	//w findPath do kazdego pola byla dolaczana informacja skad przyszedl. Ale ta informacja nie byla wystarczajaca aby dostac tak od reki tablice punktow 
	//po ktorych nalezy przejsc aby dojsc do celu
	//wpiermy bierzemy pozycje current_node. pierwsza iteracja jest od end_node
	Position nCurrentPosition(currentNode->position);
	//potem szukamy tego czegos w came_from (odpowiedniego node'a tylko ze w came_from
	auto from = came_from.find(nCurrentPosition);
	//jesli taki istnieje i jesli nie jest to poczatek trasy
	if (from != came_from.end() && from->first != begin)
	{
		//jedziemy glebiej z nastepna iteracja :D
		reconstructPath(came_from, path, from->second, begin);
		//wkladamy do patha biezaca pozycje
		path->path.push_back(currentNode->position);
		//zwracamy sciezke
		return path;
	}
	else
	{
		//wkladamy biezaca pozycje (prawdopodbnie ostatnia pozycja)
		path->path.push_back(currentNode->position);
		//zwracamy
		return path;
	}
}

//A* estymuje jaki jest koszt danego pola. Tutaj wykorzystuje odleglosc od dolnej czesci planszy w celu oszacowania kosztu
float Astar::Node::estimate_cost(size mapHeight)
{
	return (float)(mapHeight - position.y - 1);
}

//nizej sa klasy zdefiniowane w celu uzycia unordered_map

/// node1 == node2 <- rhp
bool Astar::Node::operator ==(Node *rhp)
{
	if (position.x == rhp->position.x && position.y == rhp->position.y) return true;
	return false;
}


bool Astar::Node::operator ==(Position &rhp)
{
	if (position.x == rhp.x && position.y == rhp.y) return true;
	return false;
}


bool Astar::Node::PositionCompare::operator ()(const Position left, const Position right)
{
	if (left.y < right.y) return true;
	else if (right.y < left.y) return false;
	else
	{
		if (left.x < right.x) return true;
		else return false;
	}
}