#pragma once
#include "map.h"
class MapIO
{
public:
	virtual ~MapIO() {} //uzywamy wskaznika na MapIO by miec dostep do odziedziczonych klas wiec musi byc wirtualny destruktor by
	//zwalaniac miejsce w klasach pochodnych.

	virtual Map * load() = 0;
	virtual void save(const Path *) = 0;
};