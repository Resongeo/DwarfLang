#include "Haste.h"

#include "Lexer.h"
#include "Parser.h"
#include "ASTPrinter.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>

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
		auto parser = Parser(tokens);

		std::cout << ASTPrinter().Print(parser.Parse()) << std::endl;
	}

	void Haste::PrintInfo()
	{
		std::cout << "Welcome to the Haste Language!" << std::endl;
	}

	void Haste::Error(const String& message, size_t line)
	{
		std::cout << "[ERROR] Line: " << line << " " << message << std::endl;
		s_Instance->m_Error = true;
	}

	void Haste::Error(const Token& token, const String& message)
	{
		if (token.Type == TokenType::FILE_END)
		{
			std::cout << "[ERROR] Line: " << token.Line << " at end: " << message << std::endl;
		}
		else
		{
			std::cout << "[ERROR] Line: " << token.Line << " at " << token.Value.ToString() << ": " << message << std::endl;
		}

		throw std::exception();
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