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
		void AddToken(TokenType type);
		void AddToken(TokenType type, const String& value);

		char Advance();
		bool MatchNext(char expected);
		bool IsEndOfSource();

	private:
		String m_Source;
		Vector<Token> m_Tokens;

		int m_Start = 0;
		int m_Current = 0;
		int m_Line = 1;
	};
}