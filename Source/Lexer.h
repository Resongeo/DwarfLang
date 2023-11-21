#pragma once

#include "Token.h"

namespace HasteLang
{
	class Lexer
	{
	public:
		Lexer(const String& source);

		Vector<Token> GetTokens();

	private:
		void GetNextToken();
		void GetString();
		void GetNumber();
		void GetIdentifier();
		void AddToken(TokenType type);
		void AddToken(TokenType type, const String& value);

		char Advance();
		char Peek();
		char PeekNext();
		bool MatchNext(char expected);
		bool IsDigit(char character);
		bool IsAlpha(char character);
		bool IsAlphaNumeric(char character);
		bool EndOfSource();

	private:
		String m_Source;
		Vector<Token> m_Tokens;
		HashMap<String, TokenType> m_Keywords;

		size_t m_Start = 0;
		size_t m_Current = 0;
		size_t m_Line = 1;
	};
}