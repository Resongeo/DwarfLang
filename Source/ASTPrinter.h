#pragma once

#include "ExprVisitor.h"
#include "Expr.h"

namespace HasteLang
{
	class ASTPrinter : ExprVisitor
	{
	public:
		ASTPrinter() = default;

		String Print(const ExprRef& expr);

		String VisitBinaryExpr(BinaryExpr* binaryExpr) override;
		String VisitGroupExpr(GroupExpr* groupExpr) override;
		String VisitLiteralExpr(LiteralExpr* literalExpr) override;
		String VisitUnaryExpr(UnaryExpr* unaryExpr) override;

	private:
		String Parenthesize(const String& name, const Vector<ExprRef>& exprs);
	};
}