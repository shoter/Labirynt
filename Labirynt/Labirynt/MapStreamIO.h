#pragma once
#include "MapIO.h"

class MapStreamIO : public MapIO
{
	// Inherited via MapIO
	virtual Map * load() override;
	virtual void save(const Path *) override;
};
