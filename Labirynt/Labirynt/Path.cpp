#include "stdafx.h"
std::string Path::toString() const
{
	std::string pathStr = "";
	//iteruje od pierwszego elementu gdyz w kazdej iteracji potrzebny jest nam biezacy i poprzedni element. Element 0 nie ma poprzedniego elementu
	for (unsigned int i = 1;i < path.size();++i)
	{
		Position current = path[i];
		Position previous = path[i - 1];
		//wyliczam roznice w spolrzednych miedzy biezacym a poprzednim elementem
		int xDif = current.x - previous.x;
		int yDif = current.y - previous.y;
		//na podstawie roznicy wspolrzednych moge prosto powiedziec w jakim kierunku udal sie ten ktosiek co szedl labiryntem
		if (xDif == 1)
			pathStr += "P ";
		else if (xDif == -1)
			pathStr += "L ";
		else if (yDif == 1)
			pathStr += "D ";
		else if (yDif == -1)
			pathStr += "G ";
	}
	return pathStr;
}
