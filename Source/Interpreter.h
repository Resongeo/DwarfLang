#pragma once

#include "ExprVisitor.h"
#include "Expr.h"

namespace HasteLang
{
	class Interpreter : public ExprVisitor
	{
	public:
		Interpreter() = default;

		String Interpret(const ExprRef& expr);

		Object VisitBinaryExpr(BinaryExpr* binaryExpr) override;
		Object VisitGroupExpr(GroupExpr* groupExpr) override;
		Object VisitLiteralExpr(LiteralExpr* literalExpr) override;
		Object VisitUnaryExpr(UnaryExpr* unaryExpr) override;

	private:
		String Stringify(Object& object);

		Object Evaluate(Expr* expr);
		Object Evaluate(ExprRef expr);
		bool IsTruthy(Object& object);
		bool IsEqual(Object& a, Object& b);
		void CheckNumberOperand(const Token& op, Object& operand);
		void CheckNumberOperands(const Token& op, Object& left, Object& right);
	};
}