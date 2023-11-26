#pragma once

#include "Expr.h"
#include "Token.h"

namespace HasteLang
{
	class Parser
	{
	public:
		Parser(const Vector<Token>& tokens);

		ExprRef Parse();

	private:
		ExprRef Expression();
		ExprRef Equality();
		ExprRef Comparison();
		ExprRef Term();
		ExprRef Factor();
		ExprRef Unary();
		ExprRef Primary();

		bool Match(std::initializer_list<TokenType> types);
		bool Check(TokenType type);
		bool IsAtEnd();
		Token Advance();
		Token Peek();
		Token Previous();
		Token Consume(TokenType type, const String& message);

	private:
		Vector<Token> m_Tokens;
		size_t m_Current = 0;
	};
}