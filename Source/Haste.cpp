#include "Haste.h"

#include "Lexer.h"
#include "ASTPrinter.h"

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

		ExprRef left = CreateRef<UnaryExpr>(
			CreateRef<LiteralExpr>("123"),
			Token(TokenType::MINUS, "-", 1)
		);
		Token op(TokenType::STAR, "*", 1);
		ExprRef right = CreateRef<GroupExpr>(
			CreateRef<LiteralExpr>("3.14")
		);

		ExprRef expression = CreateRef<BinaryExpr>(left, op, right);

		std::cout << ASTPrinter().Print(expression) << std::endl;
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