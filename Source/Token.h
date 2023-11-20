#pragma once

#include "TokenType.h"
#include <string>

namespace HasteLang
{
	class Token
	{
	public:
		Token(TokenType type, const std::string& lexeme, const std::string& value, int line)
			: Type(type), Lexeme(lexeme), Value(value), Line(line) { }

		TokenType Type;
		std::string Lexeme;
		std::string Value;
		int Line;
	};
}