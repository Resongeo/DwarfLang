#include "Haste.h"
using namespace HasteLang;

#include <iostream>

int main(int argc, char* argv[])
{
	if (argc <= 1)
	{
		Haste::PrintInfo();
	}
	else if (argc >= 2)
	{
		if (String(argv[1]) == "-f" || String(argv[1]) == "-F")
		{
			if (argc <= 2)
			{
				std::cout << "No input file" << std::endl;
			}
			else
			{
				Haste haste(String(argv[2]), InputSource::File);
				haste.Run();
			}
		}
		else
		{
			Haste haste(String(argv[1]), InputSource::User);
			haste.Run();
		}
	}

	return 0;
}