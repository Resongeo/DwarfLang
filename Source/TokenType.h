#pragma once

namespace HasteLang
{
	enum class TokenType
	{
		/* Single character tokens */
		LEFT_PAREN,			// (
		RIGHT_PAREN,		// )
		LEFT_BRACE,			// {
		RIGHT_BRACE,		// }
		LEFT_SQUARE_BRACE,	// [
		RIGHT_SQUARE_BRACE,	// ]
		COMMA,				// ,
		DOT,				// .
		SEMICOLON,			// ;
		PLUS,				// +
		MINUS,				// -
		STAR,				// *
		SLASH,				// /

		/* One or two character tokens */
		EQUAL,			// =
		DOUBLE_EQUAL,	// ==
		BANG,			// !
		BANG_EQUAL,		// !=
		GREATER,		// >
		GREATER_EQUAL,	// >=
		LESS,			// <
		LESS_EQUAL,		// <=

		/* Literals */
		IDENTIFIER,	// e.g. variableName
		STRING,		// e.g. "string"
		NUMBER,		// e.g. 42

		/* Keywords */
		TRUE,
		FALSE,
		AND,
		OR,
		IF,
		ELSE,
		FOR,
		WHILE,
		CLASS,
		THIS,
		BASE,
		RETURN,
		FUNC,
		PRINT,
		VAR,

		FILE_END
	};
}
