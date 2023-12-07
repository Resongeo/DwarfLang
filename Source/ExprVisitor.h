#pragma once

#include "Types.h"
#include "ExprFwd.h"

namespace HasteLang
{
	class ExprVisitor
	{
	public:
		virtual Object VisitBinaryExpr(BinaryExpr* binaryExpr) = 0;
		virtual Object VisitGroupExpr(GroupExpr* groupExpr) = 0;
		virtual Object VisitLiteralExpr(LiteralExpr* literalExpr) = 0;
		virtual Object VisitUnaryExpr(UnaryExpr* unaryExpr) = 0;
		virtual Object VisitVariableExpr(VariableExpr* variableExpr) = 0;
	};
}