#pragma once

#include "Types.h"
#include "Token.h"
#include "ExprVisitor.h"

namespace HasteLang
{
	class Expr
	{
	public:
		Expr() = default;
		virtual String Accept(ExprVisitor& visitor) = 0;
	};

	using ExprRef = Ref<Expr>;

	class BinaryExpr : public Expr
	{
	public:
		BinaryExpr(ExprRef left, Token op, ExprRef right);
		String Accept(ExprVisitor& visitor) override;

		ExprRef Left;
		Token Operand;
		ExprRef Right;
	};

	class GroupExpr : public Expr
	{
	public:
		GroupExpr(ExprRef expression);
		String Accept(ExprVisitor& visitor) override;

		ExprRef Expression;
	};

	class LiteralExpr : public Expr
	{
	public:
		LiteralExpr(Object value);
		String Accept(ExprVisitor& visitor) override;

		Object Value;
	};

	class UnaryExpr : public Expr
	{
	public:
		UnaryExpr(Token op, ExprRef right);
		String Accept(ExprVisitor& visitor) override;

		Token Operand;
		ExprRef Right;
	};
}