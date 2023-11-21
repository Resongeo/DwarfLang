#pragma once

#include "Token.h"

namespace HasteLang
{
	class Lexer
	{
	public:
		Lexer(const String& source) : m_Source(source) { }

		Vector<Token> GetTokens();

	private:
		void GetNextToken();
		void GetString();
		void GetNumber();
		void AddToken(TokenType type);
		void AddToken(TokenType type, const String& value);

		char Advance();
		char Peek();
		char PeekNext();
		bool MatchNext(char expected);
		bool IsDigit(char character);
		bool EndOfSource();

	private:
		String m_Source;
		Vector<Token> m_Tokens;

		size_t m_Start = 0;
		size_t m_Current = 0;
		size_t m_Line = 1;
	};
}