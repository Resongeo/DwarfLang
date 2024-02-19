#pragma once

#include "ExprVisitor.h"
#include "Expr.h"

namespace DwarfLang
{
	class ASTPrinter : ExprVisitor
	{
	public:
		ASTPrinter() = default;

		Object Print(const ExprRef& expr);

		Object VisitBinaryExpr(BinaryExpr* binaryExpr) override;
		Object VisitGroupExpr(GroupExpr* groupExpr) override;
		Object VisitLiteralExpr(LiteralExpr* literalExpr) override;
		Object VisitUnaryExpr(UnaryExpr* unaryExpr) override;

	private:
		Object Parenthesize(Object& object, const Vector<ExprRef>& exprs);
		Object Parenthesize(const String& name, const Vector<ExprRef>& exprs);
	};
}