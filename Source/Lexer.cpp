#include "Lexer.h"

#include "Haste.h"

namespace HasteLang
{
	Lexer::Lexer(const String& source) : m_Source(source)
	{
		m_Keywords["true"] = TokenType::TRUE;
		m_Keywords["false"] = TokenType::FALSE;
		m_Keywords["and"] = TokenType::AND;
		m_Keywords["or"] = TokenType::OR;
		m_Keywords["if"] = TokenType::IF;
		m_Keywords["else"] = TokenType::ELSE;
		m_Keywords["for"] = TokenType::FOR;
		m_Keywords["while"] = TokenType::WHILE;
		m_Keywords["class"] = TokenType::CLASS;
		m_Keywords["this"] = TokenType::THIS;
		m_Keywords["base"] = TokenType::BASE;
		m_Keywords["return"] = TokenType::RETURN;
		m_Keywords["func"] = TokenType::FUNC;
		m_Keywords["print"] = TokenType::PRINT;
		m_Keywords["var"] = TokenType::VAR;
	}

	Vector<Token> HasteLang::Lexer::GetTokens()
	{
		while (!EndOfSource())
		{
			m_Start = m_Current;
			GetNextToken();
		}

		AddToken(TokenType::FILE_END);

		return m_Tokens;
	}

	void Lexer::GetNextToken()
	{
		char ch = Advance();
		switch (ch)
		{
			/* Single character tokens */
			case '(': AddToken(TokenType::LEFT_PAREN); break;
			case ')': AddToken(TokenType::RIGHT_PAREN); break;
			case '{': AddToken(TokenType::LEFT_BRACE); break;
			case '}': AddToken(TokenType::RIGHT_BRACE); break;
			case ',': AddToken(TokenType::COMMA); break;
			case '.': AddToken(TokenType::DOT); break;
			case ';': AddToken(TokenType::SEMICOLON); break;
			case '+': AddToken(TokenType::PLUS); break;
			case '-': AddToken(TokenType::MINUS); break;
			case '*': AddToken(TokenType::STAR); break;
			case '/': AddToken(TokenType::SLASH); break;

			/* One or two character tokens */
			case '=': AddToken(MatchNext('=') ? TokenType::DOUBLE_EQUAL : TokenType::EQUAL); break;
			case '!': AddToken(MatchNext('=') ? TokenType::BANG_EQUAL : TokenType::BANG); break;
			case '>': AddToken(MatchNext('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER); break;
			case '<': AddToken(MatchNext('=') ? TokenType::LESS_EQUAL : TokenType::LESS); break;

			/* String literals */
			case '"': GetString(); break;

			/* Whitespaces */
			case ' ': break;
			case '\r': break;
			case '\t': break;

			/* New line */
			case '\n': m_Line++; break;

			/* Comments */
			case '#':
			{
				while (Peek() != '\n' && !EndOfSource())
				{
					Advance();
				}
				break;
			}

			/* Numbers, keywords, identifiers or unexpected characters */
			default:
			{
				if (IsDigit(ch))
				{
					GetNumber();
				}
				else if (IsAlpha(ch))
				{
					GetIdentifier();
				}
				else
				{
					Haste::Error(String("Unexpected character: ") + ch, m_Line);
				}

				break;
			}
		}
	}

	void Lexer::GetString()
	{
		while (Peek() != '"' && !EndOfSource())
		{
			if (Peek() == '\n')
			{
				m_Line++;
			}
			Advance();
		}

		if (EndOfSource())
		{
			Haste::Error("Unterminated string", m_Line);
			return;
		}

		Advance();

		String value = m_Source.substr(m_Start + 1, (m_Current - m_Start) - 2);
		AddToken(TokenType::STRING, value);
	}

	void Lexer::GetNumber()
	{
		while (IsDigit(Peek())) Advance();

		if (Peek() == '.' && IsDigit(PeekNext()))
		{
			Advance();

			while (IsDigit(Peek())) Advance();
		}

		AddToken(TokenType::NUMBER);
	}

	void Lexer::GetIdentifier()
	{
		while (IsAlphaNumeric(Peek())) Advance();

		String value = m_Source.substr(m_Start, m_Current - m_Start);
		TokenType type = TokenType::IDENTIFIER;

		if (m_Keywords.find(value) != m_Keywords.end())
		{
			type = m_Keywords[value];
		}

		AddToken(type);
	}

	void Lexer::AddToken(TokenType type)
	{
		String value = m_Source.substr(m_Start, m_Current - m_Start);
		m_Tokens.push_back(Token(type, value, m_Line));
	}

	void Lexer::AddToken(TokenType type, const String& value)
	{
		m_Tokens.push_back(Token(type, value, m_Line));
	}

	char Lexer::Advance()
	{
		m_Current++;
		return m_Source[m_Current - 1];
	}

	char Lexer::Peek()
	{
		if (EndOfSource()) return '\0';
		return m_Source[m_Current];
	}

	char Lexer::PeekNext()
	{
		if (m_Current + 1 >= m_Source.size()) return '\0';
		return m_Source[m_Current + 1];
	}

	bool Lexer::MatchNext(char expected)
	{
		if (EndOfSource()) return false;
		if (m_Source[m_Current] != expected) return false;

		m_Current++;
		return true;
	}

	bool Lexer::IsDigit(char character)
	{
		return character >= '0' && character <= '9';
	}

	bool Lexer::IsAlpha(char character)
	{
		return
			(character >= 'a' && character <= 'z') ||
			(character >= 'A' && character <= 'Z') ||
			(character == '_');
	}

	bool Lexer::IsAlphaNumeric(char character)
	{
		return IsDigit(character) || IsAlpha(character);
	}

	bool Lexer::EndOfSource()
	{
		return m_Current >= m_Source.size();
	}
}
