#include "ASTPrinter.h"

namespace HasteLang
{
	String ASTPrinter::Print(const ExprRef& expr)
	{
		return expr->Accept(*this);
	}

	String ASTPrinter::VisitBinaryExpr(BinaryExpr* binaryExpr)
	{
		return Parenthesize(binaryExpr->Operand.Value, {binaryExpr->Left, binaryExpr->Right});
	}

	String ASTPrinter::VisitGroupExpr(GroupExpr* groupExpr)
	{
		return Parenthesize("group", { groupExpr->Expression });
	}

	String ASTPrinter::VisitLiteralExpr(LiteralExpr* literalExpr)
	{
		return literalExpr->Value.ToString();
	}

	String ASTPrinter::VisitUnaryExpr(UnaryExpr* unaryExpr)
	{
		return Parenthesize(unaryExpr->Operand.Value, { unaryExpr->Right });
	}

	String ASTPrinter::Parenthesize(Object& object, const Vector<ExprRef>& exprs)
	{
		String result;
		result.append("(");
		result.append(object.ToString());

		for (auto& expr : exprs)
		{
			result.append(" ");
			result.append(expr->Accept(*this));
		}

		result.append(")");

		return result;
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


