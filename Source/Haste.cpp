#include "Haste.h"

#include "Lexer.h"

#include <iostream>
#include <fstream>
#include <sstream>

namespace HasteLang
{
	Haste* Haste::s_Instance = nullptr;

	Haste::Haste(const String& filepath)
	{
		s_Instance = this;
		m_Source = ReadFile(filepath);
	}

	void Haste::Run()
	{
		auto lexer = Lexer(m_Source);
		auto tokens = lexer.GetTokens();
	}

	void Haste::PrintInfo()
	{
		std::cout << "Welcome to the Haste Language!" << std::endl;
	}

	void Haste::Error(const String& message, int line)
	{
		std::cout << "[ERROR] Line: " << line << " " << message << std::endl;
		s_Instance->m_Error = true;
	}

	String Haste::ReadFile(const String& filepath)
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