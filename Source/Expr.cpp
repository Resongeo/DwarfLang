#include "Expr.h"

namespace HasteLang
{
	BinaryExpr::BinaryExpr(ExprRef left, Token op, ExprRef right)
		: Left(std::move(left)), Operand(std::move(op)), Right(std::move(right)) { }
	Object BinaryExpr::Accept(ExprVisitor& visitor) { return visitor.VisitBinaryExpr(this); }

	GroupExpr::GroupExpr(ExprRef expression)
		: Expression(std::move(expression)) { }
	Object GroupExpr::Accept(ExprVisitor& visitor) { return visitor.VisitGroupExpr(this); }

	LiteralExpr::LiteralExpr(Object value)
		: Value(std::move(value)) { }
	Object LiteralExpr::Accept(ExprVisitor& visitor) { return visitor.VisitLiteralExpr(this); }

	UnaryExpr::UnaryExpr(Token op, ExprRef right)
		: Operand(std::move(op)), Right(std::move(right)) { }
	Object UnaryExpr::Accept(ExprVisitor& visitor) { return visitor.VisitUnaryExpr(this); }
}