#pragma once

#include "TokenType.h"
#include "Types.h"

namespace DwarfLang
{
	class Token
	{
	public:
		Token(TokenType type, const Object& value, size_t line)
			: Type(type), Value(value), Line(line) { }

		TokenType Type;
		Object Value;
		size_t Line;
	};
}