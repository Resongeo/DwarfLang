#pragma once

#include "Stmt.h"

namespace HasteLang
{
	class Parser
	{
	public:
		Parser(const Vector<Token>& tokens);

		Vector<StmtRef> Parse();

	private:
		StmtRef Declaration();
		StmtRef Statement();
		StmtRef PrintStatement();
		StmtRef ExpressionStatement();
		StmtRef VarStatement();

		ExprRef Expression();
		ExprRef Assignment();
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