#include "stdafx.h"
#include "ConvertException.h"
//blad konwertowania w Converterze
ConvertException::ConvertException() :
	std::exception("Converting failed. Check the input")//on to wyswietla jak zostanie rzucony. Nic wiecej.
{
}
