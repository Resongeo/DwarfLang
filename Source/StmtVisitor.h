#pragma once

#include "StmtFwd.h"

namespace HasteLang
{
	class StmtVisitor
	{
	public:
		virtual void VisitExpressionStmt(ExpressionStmt* exprStmt) = 0;
		virtual void VisitPrintStmt(PrintStmt* printStmt) = 0;
		virtual void VisitVarStmt(VarStmt* varStmt) = 0;
	};
}