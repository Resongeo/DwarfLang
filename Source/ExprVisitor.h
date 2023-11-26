#pragma once

#include "Types.h"
#include "ExprFwd.h"

namespace HasteLang
{
	class ExprVisitor
	{
	public:
		virtual String VisitBinaryExpr(BinaryExpr* binaryExpr) = 0;
		virtual String VisitGroupExpr(GroupExpr* groupExpr) = 0;
		virtual String VisitLiteralExpr(LiteralExpr* literalExpr) = 0;
		virtual String VisitUnaryExpr(UnaryExpr* unaryExpr) = 0;
	};
}