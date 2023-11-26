#include "ASTPrinter.h"

namespace HasteLang
{
	String ASTPrinter::Print(const ExprRef& expr)
	{
		return expr->Accept(*this);
	}

	String ASTPrinter::VisitBinaryExpr(BinaryExpr* binaryExpr)
	{
		return Parenthesize(binaryExpr->Operand.Value, { binaryExpr->Left, binaryExpr->Right });
	}

	String ASTPrinter::VisitGroupExpr(GroupExpr* groupExpr)
	{
		return Parenthesize("group", { groupExpr->Expression });
	}

	String ASTPrinter::VisitLiteralExpr(LiteralExpr* literalExpr)
	{
		return literalExpr->Value.empty() ? "null" : literalExpr->Value;
	}

	String ASTPrinter::VisitUnaryExpr(UnaryExpr* unaryExpr)
	{
		return Parenthesize(unaryExpr->Operand.Value, { unaryExpr->Right });
	}

	String ASTPrinter::Parenthesize(const String& name, const Vector<ExprRef>& exprs)
	{
		String result;
		result.append("(");
		result.append(name);

		for (auto& expr : exprs)
		{
			result.append(" ");
			result.append(expr->Accept(*this));
		}

		result.append(")");

		return result;
	}
}


