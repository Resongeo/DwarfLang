#include "Haste.h"
using namespace HasteLang;

#include <iostream>

int main(int argc, char* argv[])
{
	if (argc <= 1)
	{
		Haste::PrintInfo();
	}
	else
	{
		auto filepath = String(argv[1]);
		Haste haste(filepath);
		haste.Run();
	}

	return 0;
}