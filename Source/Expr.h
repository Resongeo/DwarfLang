#pragma once

#include "Types.h"
#include "Token.h"
#include "ExprVisitor.h"

namespace DwarfLang
{
	class Expr
	{
	public:
		Expr() = default;
		virtual Object Accept(ExprVisitor* visitor) = 0;
	};

	using ExprRef = Ref<Expr>;

	class BinaryExpr : public Expr
	{
	public:
		BinaryExpr(ExprRef left, Token op, ExprRef right);
		Object Accept(ExprVisitor* visitor) override;

		ExprRef Left;
		Token Operator;
		ExprRef Right;
	};

	class GroupExpr : public Expr
	{
	public:
		GroupExpr(ExprRef expression);
		Object Accept(ExprVisitor* visitor) override;

		ExprRef Expression;
	};

	class LiteralExpr : public Expr
	{
	public:
		LiteralExpr(Object value);
		Object Accept(ExprVisitor* visitor) override;

		Object Value;
	};

	class UnaryExpr : public Expr
	{
	public:
		UnaryExpr(Token op, ExprRef right);
		Object Accept(ExprVisitor* visitor) override;

		Token Operand;
		ExprRef Right;
	};

	class VariableExpr : public Expr
	{
	public:
		VariableExpr(Token name);
		Object Accept(ExprVisitor* visitor) override;

		Token Name;
	};

	class AssignExpr : public Expr
	{
	public:
		AssignExpr(Token name, ExprRef value);
		Object Accept(ExprVisitor* visitor) override;

		Token Name;
		ExprRef Value;
	};
}