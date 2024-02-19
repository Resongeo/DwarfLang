#include "Dwarf.h"

#include "Lexer.h"
#include "Parser.h"
#include "ASTPrinter.h"
#include "Interpreter.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>

namespace DwarfLang
{
	Dwarf* Dwarf::s_Instance = nullptr;

	Dwarf::Dwarf(const String& source, InputSource inputSource)
	{
		s_Instance = this;
		m_Source = inputSource == InputSource::File ? ReadFile(source) : source;
	}

	void Dwarf::Run()
	{
		auto tokens = Lexer(m_Source).GetTokens();
		auto statements = Parser(tokens).Parse();
		Interpreter().Interpret(statements);
	}

	void Dwarf::PrintInfo()
	{
		std::cout << "Welcome to the Dwarf Language!" << std::endl;
	}

	void Dwarf::Error(const String& message)
	{
		std::cout << "[ERROR]: " << message << std::endl;
		s_Instance->m_Error = true;
	}

	void Dwarf::Error(const String& message, size_t line)
	{
		std::cout << "[ERROR] Line: " << line << " " << message << std::endl;
		s_Instance->m_Error = true;
	}

	void Dwarf::Error(const Token& token, const String& message)
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

	String Dwarf::ReadFile(const String& filepath)
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