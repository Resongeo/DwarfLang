#include "Parser.h"

#include "Dwarf.h"

namespace DwarfLang
{
	Parser::Parser(const Vector<Token>& tokens) : m_Tokens(tokens) { }

	Vector<StmtRef> Parser::Parse()
	{
		Vector<StmtRef> statements;

		while (!IsAtEnd())
		{
			statements.push_back(Declaration());
		}

		return statements;
	}

	StmtRef Parser::Declaration()
	{
		if (Match({ TokenType::VAR })) return VarStatement();
		return Statement();
	}

	StmtRef Parser::Statement()
	{
		if (Match({ TokenType::PRINT })) return PrintStatement();
		return ExpressionStatement();
	}

	StmtRef Parser::PrintStatement()
	{
		ExprRef expr = Expression();
		Consume(TokenType::SEMICOLON, "Expected ';' after value");
		return CreateRef<PrintStmt>(expr);
	}

	StmtRef Parser::ExpressionStatement()
	{
		ExprRef expr = Expression();
		Consume(TokenType::SEMICOLON, "Expected ';' after expression");
		return CreateRef<ExpressionStmt>(expr);
	}

	StmtRef Parser::VarStatement()
	{
		Token name = Consume(TokenType::IDENTIFIER, "Expected variable name");
		
		ExprRef initializer = nullptr;
		if (Match({ TokenType::EQUAL })) initializer = Expression();

		Consume(TokenType::SEMICOLON, "Expected ';' after variable declaration");
		return CreateRef<VarStmt>(name, initializer);
	}

	ExprRef Parser::Expression()
	{
		return Assignment();
	}

	ExprRef Parser::Assignment()
	{
		ExprRef expr = Equality();

		if (Match({ TokenType::EQUAL }))
		{
			auto op = Previous();
			auto value = Assignment();

			if (VariableExpr* varExpr = dynamic_cast<VariableExpr*>(expr.get()))
			{
				return CreateRef<AssignExpr>(varExpr->Name, value);
			}

			Dwarf::Error(op, "Invalid assignment target");
		}

		return expr;
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

		if (Match({ TokenType::IDENTIFIER })) return CreateRef<VariableExpr>(Previous());

		if (Match({ TokenType::LEFT_PAREN }))
		{
			auto expr = Expression();
			Consume(TokenType::RIGHT_PAREN, "Expected ')' after expression");
			return CreateRef<GroupExpr>(expr);
		}

		Dwarf::Error(Peek(), "Expected expression");
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

		Dwarf::Error(Peek(), message);
	}
}