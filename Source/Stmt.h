#pragma once

#include "Expr.h"
#include "StmtVisitor.h"

namespace DwarfLang
{
	class Stmt
	{
	public:
		Stmt() = default;
		virtual void Accept(StmtVisitor* visitor) = 0;
	};

	using StmtRef = Ref<Stmt>;

	class ExpressionStmt : public Stmt
	{
	public:
		ExpressionStmt(ExprRef expr);
		void Accept(StmtVisitor* visitor);

		ExprRef Expression;
	};

	class PrintStmt : public Stmt
	{
	public:
		PrintStmt(ExprRef expr);
		void Accept(StmtVisitor* visitor);

		ExprRef Expression;
	};

	class VarStmt : public Stmt
	{
	public:
		VarStmt(Token name, ExprRef initializer);
		void Accept(StmtVisitor* visitor);

		Token Name;
		ExprRef Initializer;
	};
};