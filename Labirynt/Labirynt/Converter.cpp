#include "stdafx.h"
#include "Converter.h"
#include "ConvertException.h"

//Konwertuje znak na tile
TileType Converter::convertToTileType(const char character)
{
	switch (character)
	{
	case 'B' :
		return TileType::Free;
	case 'C' :
		return TileType::Occupied;
	}
	throw ConvertException();
}
//konwertuje tile na znak (nieuzywane, nie usuniete bo skoro zostalo juz odruchowo napisane to lepiej zostawic)
char Converter::convertToChar(const TileType tile)
{
	switch(tile)
	{
	case TileType::Free :
		return 'B';
	case TileType::Occupied :
		return 'C';
	}
	throw ConvertException();
}
//zmienia tile na znak ktory ladnie wyglada dla oka :)
char Converter::convertToDisplayDebug(const TileType tile)
{
	switch (tile)
	{
	case TileType::Free:
		return '.';
	case TileType::Occupied:
		return '#';
	}
	throw ConvertException();
}
