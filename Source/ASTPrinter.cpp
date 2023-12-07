#include "ASTPrinter.h"

namespace HasteLang
{
	Object ASTPrinter::Print(const ExprRef& expr)
	{
		return expr->Accept(this);
	}

	Object ASTPrinter::VisitBinaryExpr(BinaryExpr* binaryExpr)
	{
		return Parenthesize(binaryExpr->Operator.Value, {binaryExpr->Left, binaryExpr->Right});
	}

	Object ASTPrinter::VisitGroupExpr(GroupExpr* groupExpr)
	{
		return Parenthesize("group", { groupExpr->Expression });
	}

	Object ASTPrinter::VisitLiteralExpr(LiteralExpr* literalExpr)
	{
		return literalExpr->Value.ToString();
	}

	Object ASTPrinter::VisitUnaryExpr(UnaryExpr* unaryExpr)
	{
		return Parenthesize(unaryExpr->Operand.Value, { unaryExpr->Right });
	}

	Object ASTPrinter::Parenthesize(Object& object, const Vector<ExprRef>& exprs)
	{
		String result;
		result.append("(");
		result.append(object.ToString());

		for (auto& expr : exprs)
		{
			result.append(" ");
			result.append(expr->Accept(this).ToString());
		}

		result.append(")");

		return result;
	}

	Object ASTPrinter::Parenthesize(const String& name, const Vector<ExprRef>& exprs)
	{
		String result;
		result.append("(");
		result.append(name);

		for (auto& expr : exprs)
		{
			result.append(" ");
			result.append(expr->Accept(this).ToString());
		}

		result.append(")");

		return Object(result);
	}
}


