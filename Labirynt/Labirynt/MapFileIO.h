#pragma once
#include "MapIO.h"
#include <string>

class MapFileIO : public MapIO
{
public:
	MapFileIO(const std::string & inputFile, const std::string & outputFile);

	// Inherited via MapIO
	virtual Map* load() override;

	virtual void save(const Path *) override;

protected:
	const std::string inputFile, outputFile;

};
