#include "Haste.h"

#include <iostream>
#include <fstream>
#include <sstream>

namespace HasteLang
{
	Haste::Haste(const std::string& source, SourceType sourceType)
	{
		m_Source = sourceType == SourceType::String ? source : ReadFile(source);
	}

	void Haste::Run()
	{

	}

	void Haste::PrintInfo()
	{
		std::cout << "Welcome to the Haste Language!" << std::endl;
	}

	std::string Haste::ReadFile(const std::string& filepath)
	{
		std::ifstream file(filepath);
		std::ostringstream ss;

		if (file)
		{
			ss << file.rdbuf();
		}

		return ss.str();
	}
}