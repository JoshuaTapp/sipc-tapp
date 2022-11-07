#pragma once

#include "ASTExpr.h"

/*! \brief Class for representing a ternary expression.
 *
 * A ternary expression is an expression of the form
 * <expr> ? <expr> : <expr>
 */

class ASTTernaryExpr : public ASTExpr
{
    std::shared_ptr<ASTExpr> cond, trueExpr, falseExpr;

public:
    ASTTernaryExpr(std::unique_ptr<ASTExpr> cond, std::unique_ptr<ASTExpr> trueExpr, std::unique_ptr<ASTExpr> falseExpr)
        : cond(std::move(cond)), trueExpr(std::move(trueExpr)), falseExpr(std::move(falseExpr)) {}
    ASTExpr *getCond() const { return cond.get(); }
    ASTExpr *getTrueExpr() const { return trueExpr.get(); }
    ASTExpr *getFalseExpr() const { return falseExpr.get(); }
    void accept(ASTVisitor *visitor) override;
    std::vector<std::shared_ptr<ASTNode>> getChildren() override;
    llvm::Value *codegen() override;

protected:
    std::ostream &print(std::ostream &out) const override;
};