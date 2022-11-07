#pragma once

#include "ASTExpr.h"

/*! \brief Class for a unary operator.

    \note currently only supports arithmetic negation and logical negation.
*/

class ASTUnaryExpr : public ASTExpr
{
    std::string OP;
    std::shared_ptr<ASTExpr> expr;

public:
    std::vector<std::shared_ptr<ASTNode>> getChildren() override;
    ASTUnaryExpr(const std::string &OP, std::unique_ptr<ASTExpr> expr)
        : OP(OP), expr(std::move(expr)) {}
    std::string getOp() const { return OP; }
    ASTExpr *getExpr() const { return expr.get(); }
    void accept(ASTVisitor *visitor) override;
    llvm::Value *codegen() override;

protected:
    std::ostream &print(std::ostream &out) const override;
};