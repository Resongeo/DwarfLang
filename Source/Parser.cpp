#include "Parser.h"

#include "Haste.h"

namespace HasteLang
{
	Parser::Parser(const Vector<Token>& tokens) : m_Tokens(tokens) { }

	ExprRef Parser::Parse()
	{
		return Expression();
	}

	ExprRef Parser::Expression()
	{
		return Equality();
	}

	ExprRef Parser::Equality()
	{
		ExprRef expr = Comparison();

		while (Match({ TokenType::BANG_EQUAL, TokenType::DOUBLE_EQUAL }))
		{
			auto op = Previous();
			auto right = Comparison();
			expr = CreateRef<BinaryExpr>(expr, op, right);
		}

		return expr;
	}

	ExprRef Parser::Comparison()
	{
		ExprRef expr = Term();

		while (Match({ TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL }))
		{
			auto op = Previous();
			auto right = Term();
			expr = CreateRef<BinaryExpr>(expr, op, right);
		}

		return expr;
	}

	ExprRef Parser::Term()
	{
		ExprRef expr = Factor();

		while (Match({ TokenType::PLUS, TokenType::MINUS }))
		{
			auto op = Previous();
			auto right = Factor();
			expr = CreateRef<BinaryExpr>(expr, op, right);
		}

		return expr;
	}

	ExprRef Parser::Factor()
	{
		ExprRef expr = Unary();

		while (Match({ TokenType::SLASH, TokenType::STAR }))
		{
			auto op = Previous();
			auto right = Unary();
			expr = CreateRef<BinaryExpr>(expr, op, right);
		}

		return expr;
	}

	ExprRef Parser::Unary()
	{
		if (Match({ TokenType::BANG, TokenType::MINUS }))
		{
			auto op = Previous();
			auto right = Unary();
			return CreateRef<UnaryExpr>(op, right);
		}

		return Primary();
	}

	ExprRef Parser::Primary()
	{
		if (Match({ TokenType::FALSE })) return CreateRef<LiteralExpr>("false");
		if (Match({ TokenType::TRUE })) return CreateRef<LiteralExpr>("true");
		if (Match({ TokenType::NIL })) return CreateRef<LiteralExpr>("null");
		if (Match({ TokenType::NUMBER, TokenType::STRING })) return CreateRef<LiteralExpr>(Previous().Value);

		if (Match({ TokenType::LEFT_PAREN }))
		{
			auto expr = Expression();
			Consume(TokenType::RIGHT_PAREN, "Expected ')' after expression");
			return CreateRef<GroupExpr>(expr);
		}

		Haste::Error(Peek(), "Expected expression");
	}



	bool Parser::Match(std::initializer_list<TokenType> types)
	{
		for (auto type : types)
		{
			if (Check(type))
			{
				Advance();
				return true;
			}
		}

		return false;
	}

	bool Parser::Check(TokenType type)
	{
		if (IsAtEnd()) return false;
		return Peek().Type == type;
	}

	bool Parser::IsAtEnd()
	{
		return Peek().Type == TokenType::FILE_END;
	}

	Token Parser::Advance()
	{
		if (!IsAtEnd()) m_Current++;
		return Previous();
	}

	Token Parser::Peek()
	{
		return m_Tokens[m_Current];
	}

	Token Parser::Previous()
	{
		return m_Tokens[m_Current - 1];
	}

	Token Parser::Consume(TokenType type, const String& message)
	{
		if (Check(type)) return Advance();

		Haste::Error(Peek(), message);
	}
}