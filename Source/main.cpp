#include "Dwarf.h"
using namespace DwarfLang;

#include <iostream>

int main(int argc, char* argv[])
{
	if (argc <= 1)
	{
		Dwarf::PrintInfo();
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
				Dwarf Dwarf(String(argv[2]), InputSource::File);
				Dwarf.Run();
			}
		}
		else
		{
			Dwarf Dwarf(String(argv[1]), InputSource::User);
			Dwarf.Run();
		}
	}

	return 0;
}