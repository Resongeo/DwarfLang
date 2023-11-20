#include "Haste.h"
using namespace HasteLang;

int main(int argc, char* argv[])
{
	if (argc <= 1)
	{
		Haste::PrintInfo();
	}
	else
	{
		Haste haste(std::string(argv[1]), SourceType::String);
		haste.Run();
	}

	return 0;
}