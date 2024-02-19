#pragma once

#include "Environment.h"
#include "ExprVisitor.h"
#include "StmtVisitor.h"
#include "Expr.h"
#include "Stmt.h"

namespace DwarfLang
{
	class Interpreter : public ExprVisitor, public StmtVisitor
	{
	public:
		Interpreter() = default;

		void Interpret(const Vector<StmtRef>& statements);

		Object VisitBinaryExpr(BinaryExpr* binaryExpr) override;
		Object VisitGroupExpr(GroupExpr* groupExpr) override;
		Object VisitLiteralExpr(LiteralExpr* literalExpr) override;
		Object VisitUnaryExpr(UnaryExpr* unaryExpr) override;
		Object VisitVariableExpr(VariableExpr* variableExpr) override;
		Object VisitAssignExpr(AssignExpr* assignExpr) override;

		void VisitExpressionStmt(ExpressionStmt* exprStmt) override;
		void VisitPrintStmt(PrintStmt* printStmt) override;
		void VisitVarStmt(VarStmt* varStmt) override;

	private:
		void Execute(StmtRef stmt);
		String Stringify(Object& object);

		Object Evaluate(Expr* expr);
		Object Evaluate(ExprRef expr);
		bool IsTruthy(Object& object);
		bool IsEqual(Object& a, Object& b);
		void CheckNumberOperand(const Token& op, Object& operand);
		void CheckNumberOperands(const Token& op, Object& left, Object& right);

	private:
		Environment m_Environment;
	};
}