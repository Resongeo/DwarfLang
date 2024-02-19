#include "Stmt.h"

namespace DwarfLang
{
	ExpressionStmt::ExpressionStmt(ExprRef expr) : Expression(std::move(expr)) { }
	void ExpressionStmt::Accept(StmtVisitor* visitor) { visitor->VisitExpressionStmt(this); }

	PrintStmt::PrintStmt(ExprRef expr) : Expression(std::move(expr)) { }
	void PrintStmt::Accept(StmtVisitor* visitor) { visitor->VisitPrintStmt(this); }

	VarStmt::VarStmt(Token name, ExprRef initializer) : Name(std::move(name)), Initializer(std::move(initializer)) {}
	void VarStmt::Accept(StmtVisitor* visitor) { visitor->VisitVarStmt(this); }
}