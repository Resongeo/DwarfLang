#pragma once

#include "TokenType.h"
#include "Types.h"

namespace HasteLang
{
	class Token
	{
	public:
		Token(TokenType type, const String& value, size_t line)
			: Type(type), Value(value), Line(line) { }

		TokenType Type;
		String Value;
		size_t Line;
	};
}