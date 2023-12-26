#include "Interpreter.h"
#include "Haste.h"

#include <iostream>

namespace HasteLang
{
	void Interpreter::Interpret(const Vector<StmtRef>& statements)
	{
		for (auto& statement : statements)
		{
			Execute(statement);
		}
	}

	Object Interpreter::VisitBinaryExpr(BinaryExpr* binaryExpr)
	{
		Object left = Evaluate(binaryExpr->Left);
		Object right = Evaluate(binaryExpr->Right);
		Token op = binaryExpr->Operator;

		switch (op.Type)
		{
			case TokenType::PLUS:
			{
				if (left.GetType() == DataType::Double && right.GetType() == DataType::Double)
				{
					return left.Get<double>() + right.Get<double>();
				}

				if (left.GetType() == DataType::String && right.GetType() == DataType::String)
				{
					return left.Get<String>() + right.Get<String>();
				}

				Haste::Error(binaryExpr->Operator, "Operands must be two numbers or two strings");

				break;
			}
			case TokenType::MINUS:
			{
				CheckNumberOperand(op, right);
				return left.Get<double>() - right.Get<double>();
			}
			case TokenType::SLASH:
			{
				CheckNumberOperands(op, left, right);
				return left.Get<double>() / right.Get<double>();
			}
			case TokenType::STAR:
			{
				CheckNumberOperands(op, left, right);
				return left.Get<double>() * right.Get<double>();
			}
			case TokenType::GREATER:
			{
				CheckNumberOperands(op, left, right);
				return left.Get<double>() > right.Get<double>();
			}
			case TokenType::GREATER_EQUAL:
			{
				CheckNumberOperands(op, left, right);
				return left.Get<double>() >= right.Get<double>();
			}
			case TokenType::LESS:
			{
				CheckNumberOperands(op, left, right);
				return left.Get<double>() < right.Get<double>();
			}
			case TokenType::LESS_EQUAL:
			{
				CheckNumberOperands(op, left, right);
				return left.Get<double>() <= right.Get<double>();
			}
			case TokenType::DOUBLE_EQUAL:
			{
				CheckNumberOperands(op, left, right);
				return IsEqual(left, right);
			}
			case TokenType::BANG_EQUAL:
			{
				CheckNumberOperands(op, left, right);
				return !IsEqual(left, right);
			}
		}
	}
	
	Object Interpreter::VisitGroupExpr(GroupExpr* groupExpr)
	{
		return Evaluate(groupExpr->Expression);
	}

	Object Interpreter::VisitLiteralExpr(LiteralExpr* literalExpr)
	{
		return literalExpr->Value;
	}

	Object Interpreter::VisitUnaryExpr(UnaryExpr* unaryExpr)
	{
		Object right = Evaluate(unaryExpr->Right);

		switch (unaryExpr->Operand.Type)
		{
			case TokenType::BANG: return !IsTruthy(right);
			case TokenType::MINUS:
			{
				double& value = right.GetRef<double>();
				value = -value;

				return right;
			}
		}

		return Object();
	}

	Object Interpreter::VisitVariableExpr(VariableExpr* variableExpr)
	{
		return m_Environment.Get(variableExpr->Name);
	}

	Object Interpreter::VisitAssignExpr(AssignExpr* assignExpr)
	{
		Object value = Evaluate(assignExpr->Value);
		m_Environment.Assign(assignExpr->Name.Value.ToString(), value);

		return value;
	}

	void Interpreter::VisitExpressionStmt(ExpressionStmt* exprStmt)
	{
		Evaluate(exprStmt->Expression);
	}

	void Interpreter::VisitPrintStmt(PrintStmt* printStmt)
	{
		Object value = Evaluate(printStmt->Expression);
		std::cout << Stringify(value) << std::endl;
	}

	void Interpreter::VisitVarStmt(VarStmt* varStmt)
	{
		Object value = varStmt->Initializer != nullptr ? Evaluate(varStmt->Initializer) : Object();
		m_Environment.Define(varStmt->Name.Value.ToString(), value);
	}

	void Interpreter::Execute(StmtRef stmt)
	{
		stmt->Accept(this);
	}

	String Interpreter::Stringify(Object& object)
	{
		switch (object.GetType())
		{
			case DataType::Null: return "null";
			case DataType::Double:
			{
				String text = object.ToString();
				if (text.ends_with(".0"))
				{
					text = text.substr(0, text.size() - 2);
				}

				return text;
			}
		}

		return object.ToString();
	}

	Object Interpreter::Evaluate(Expr* expr)
	{
		return expr->Accept(this);
	}

	Object Interpreter::Evaluate(ExprRef expr)
	{
		return expr->Accept(this);
	}

	bool Interpreter::IsTruthy(Object& object)
	{
		switch (object.GetType())
		{
			case DataType::Null: return false;
			case DataType::Bool: return object.Get<bool>();
		}

		return true;
	}

	bool Interpreter::IsEqual(Object& a, Object& b)
	{
		return a.ToString() == b.ToString();
	}

	void Interpreter::CheckNumberOperand(const Token& op, Object& operand)
	{
		if (operand.GetType() == DataType::Double) return;

		Haste::Error(op, "Operand must be a number");
	}

	void Interpreter::CheckNumberOperands(const Token& op, Object& left, Object& right)
	{
		if (left.GetType() == DataType::Double && right.GetType() == DataType::Double) return;

		Haste::Error(op, "Operands must be numbers");
	}
}